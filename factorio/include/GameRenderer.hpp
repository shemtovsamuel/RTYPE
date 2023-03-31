#pragma once

#include <SFML/Graphics.hpp>

#include "MapGenerator.hpp"

#include "graphical/GraphicalWindow.hpp"

namespace factorio
{
    class GameRenderer
    {
    public:
        GameRenderer();
        ~GameRenderer();

        sf::RenderWindow& getWindow();

        sf::View& getView();

        factorio::map::MapGenerator& getMapGenerator();

        void generateMap();

        void render();
    
    private:
        factorio::graphical::GraphicalWindow _graphicalWindow;
        sf::View _view;

        factorio::map::MapGenerator _mapGenerator;
    };
}