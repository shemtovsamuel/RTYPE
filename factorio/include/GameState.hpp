#pragma once

#include <engine/ecs/EntityManager.hpp>

#include "GameLoop.hpp"
#include "GameRenderer.hpp"
#include "GameConfig.hpp"
#include "GameInput.hpp"
#include "AssetManager.hpp"
#include "debug/Debugger.hpp"
#include "debug/Logger.hpp"
#include "Components.hpp"

namespace factorio
{
    class GameState
    {
    public:
        GameState();
        ~GameState();

        engine::ecs::EntityManager<factorio::config::ComponentCount, factorio::config::SystemCount>& getEntityManager();
        GameLoop& getGameLoop();
        GameRenderer& getGameRenderer();
        GameInput& getGameInput();

        void run();

    private:
        // engine
        engine::ecs::EntityManager<factorio::config::ComponentCount, factorio::config::SystemCount> _entityManager;

        // factorio
        factorio::debug::Debugger _debugger;
        GameLoop _gameLoop;
        GameRenderer _gameRenderer;
        GameInput _gameInput;
    };
}