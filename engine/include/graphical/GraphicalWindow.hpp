#pragma once

#include <any>

namespace engine
{
    namespace graphical
    {
        class GraphicalWindow
        {
        public:
            GraphicalWindow() = default;
            virtual ~GraphicalWindow() = default;

            virtual void drawSprite(std::any sprite) = 0;
            virtual void drawRect(std::any rect) = 0;
            virtual void drawText(std::any text) = 0;
        };
    }
}