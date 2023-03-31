#pragma once

#include "GameRenderer.hpp"
#include "GameInput.hpp"
#include "debug/Debugger.hpp"
#include "debug/Logger.hpp"

namespace factorio
{
    class GameLoop
    {
    public:
        GameLoop(factorio::GameInput& gameInput, factorio::GameRenderer& gameRenderer, factorio::debug::Debugger& debugger);
        ~GameLoop();

        float getFps() const;

        void run();

    private:
        void input();
        void update();
        void render();

        factorio::debug::Debugger& _debugger;

        factorio::GameInput& _gameInput;
        factorio::GameRenderer& _gameRenderer;

        sf::Clock _dtClock;
        sf::Time _dt;
    };
}