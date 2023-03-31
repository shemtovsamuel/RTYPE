#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <set>
#include <any>
#include <unordered_map>

#include "config/EcsConfig.hpp"

#include <SFML/Graphics.hpp>

#include "systems/TransformSystem.hpp"
#include "systems/MovementSystem.hpp"
#include "systems/PlayerShootSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/HealthSystem.hpp"
#include "systems/CleanEntitySystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "systems/BossHiveShootSystem.hpp"
#include "systems/BossAlienShootSystem.hpp"
#include "systems/EnemyShootSystem.hpp"
#include "systems/LevelSystem.hpp"
#include "systems/ScoreSystem.hpp"
#include "systems/SpawnBonusSystem.hpp"

#include "LevelManager.hpp"
#include "ScoreManager.hpp"

#include "events/InputEvent.hpp"

#include "EntityTemplate.hpp"
#include "QueueManager.hpp"

namespace rtype {
    /**
     * @brief Game's base, has to be completed in a child class
     */
    class Game {
        public:
            /**
             * @brief Create base of the game
             * @param queue Queue to fill if need to send package by network
             */
            Game();

            /**
             * @brief Handle how to handle the received events
             * @param content Package to handle
             */
            virtual void handleEvent(rtype::NetworkEvent content) = 0;

            /**
             * @brief Gets the entity manager of the game
             * @return The entity manager
             */
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &getEntityManager();

            /**
             * @brief Game loop to repeat at every frame
             */
            virtual void gameLoop() = 0;

            /**
             * @brief Tells if the game is over
             * @return Boolean saying if the game is over
             */
            virtual bool isOver() = 0;

            /**
             * @brief Gets the fps of the game
             * @return Float containing the fps
             */
            virtual float getFps() const = 0;

        protected:
            /**
             * @brief Update the game
             */
            virtual void gameUpdate() = 0;

            /**
             * @brief Handle game events from the game (keyboard, mouse, ...)
             */
            virtual void gameEvent();

            std::chrono::time_point<std::chrono::steady_clock> _clockStarting;
            double _dt;
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> _entityManager;
            std::unordered_map<int, engine::ecs::Entity> _players;
    };
}