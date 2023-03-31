#pragma once

#include <SFML/Graphics.hpp>

#include <engine/graphical/GraphicalWindow.hpp>

namespace rtype
{
    namespace graphical
    {
        class GraphicalWindow : public engine::graphical::GraphicalWindow
        {
        public:
            GraphicalWindow() : _window(sf::VideoMode(1920, 1080), "R-Type")
            {
            }

            sf::RenderWindow &getWindow()
            {
                return _window;
            }

            void drawSprite(std::any sprite)
            {
                _window.draw(std::any_cast<sf::Sprite>(sprite));
            }

            void drawRect(std::any rect)
            {
                _window.draw(std::any_cast<sf::RectangleShape>(rect));
            }

            void drawText(std::any text)
            {
                _window.draw(std::any_cast<sf::Text>(text));
            }

        private:
            sf::RenderWindow _window;
        };
    }
}