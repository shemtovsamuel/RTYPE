#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <set>

#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <sol/sol.hpp>

#include <engine/ecs/Component.hpp>
#include <engine/ecs/Components.hpp>
#include <engine/ecs/EntityManager.hpp>

#include "debug/Logger.hpp"

#include "config/EcsConfig.hpp"

#include "graphical/GraphicalWindow.hpp"

#include "systems/transformSystem.hpp"
#include "systems/movementSystem.hpp"
#include "systems/SpriteSystem.hpp"
#include "systems/SpriteAnimationSystem.hpp"
#include "systems/PlayerShootSystem.hpp"
#include "systems/CollisionSystem.hpp"
#include "systems/HealthSystem.hpp"
#include "systems/CleanEntitySystem.hpp"
#include "systems/ParallaxSystem.hpp"
#include "systems/ObstacleSystem.hpp"

#include "events/inputEvent.hpp"

#include "AssetManager.hpp"
#include "EntityTemplate.hpp"

namespace rtype
{
    class Game
    {
    public:
        Game();
        ~Game();

        float getFps() const;

        engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &getEntityManager()
        {
            return _entityManager;
        }

        void gameLoop();

        void gameEvent();

        void gameUpdate();

        void gameUi();

        void gameDraw();

    private:
        rtype::graphical::GraphicalWindow _graphicalWindow;
        sol::state _lua;
        engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> _entityManager;
        rtype::AssetManager &_assetManager;
        rtype::EntityTemplate _entityTemplate;

        std::set<int> _keysToCheck = {sf::Keyboard::Space, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down};
        std::set<int> _keysPressed;
        sf::Clock _dtClock;
        sf::Time _dt;
        float _fps;
    };
}