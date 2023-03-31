#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <set>
#include <any>

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

#include "LevelManager.hpp"
#include "ScoreManager.hpp"

#include "events/InputEvent.hpp"

#include "EntityTemplate.hpp"
#include "../game/include/Game.hpp"

namespace rtype {
    /**
     * @brief Instance of the server version of the game (without graphics but having all powers)
     */
    class ServerGame : public Game {
        public:
            /**
             * @brief Constructs a game environment without any player
             * @param queue Queue of the server to fill if there are information to send to the clients
             */
            ServerGame();

            /**
             * @brief Game loop of the game to repeat while the game isn't over
             */
            void gameLoop() override;

            /**
             * @brief Says if the game is over or not
             * @return Boolean that represent the game state
             */
            bool isOver() override;

            /**
             * @brief Gets you the Fps
             * @return Float representation the actual fps (always -1 for the server)
             */
            float getFps() const override;

            /**
             * @brief Handle the events coming from the clients
             * @param content Package containing the information from the client
             */
            void handleEvent(rtype::NetworkEvent content) override;

            void gameUpdate() override;
        private:
            rtype::EntityTemplate _entityTemplate;
            rtype::LevelManager _levelManager;
            rtype::ScoreManager _scoreManager;
    };
}