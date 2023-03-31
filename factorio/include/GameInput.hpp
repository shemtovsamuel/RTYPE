#pragma once

namespace factorio
{
    class GameInput
    {
    public:
        GameInput();
        ~GameInput();

        void input();

    private:
        void handleInput();
    };
}