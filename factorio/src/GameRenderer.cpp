#include <imgui.h>
#include <imgui-SFML.h>

#include "GameRenderer.hpp"
#include "AssetManager.hpp"

factorio::GameRenderer::GameRenderer()
{
    _view = sf::View(_graphicalWindow.getWindow().getDefaultView());

    (void)ImGui::SFML::Init(_graphicalWindow.getWindow());

    _graphicalWindow.getWindow().setFramerateLimit(60);

    generateMap();
}

factorio::GameRenderer::~GameRenderer()
{
    ImGui::SFML::Shutdown();
}

sf::RenderWindow& factorio::GameRenderer::getWindow()
{
    return _graphicalWindow.getWindow();
}

sf::View& factorio::GameRenderer::getView()
{
    return _view;
}

factorio::map::MapGenerator& factorio::GameRenderer::getMapGenerator()
{
    return _mapGenerator;
}

void factorio::GameRenderer::generateMap()
{
    _mapGenerator.world = _mapGenerator.generateMap();
}

void factorio::GameRenderer::render()
{
    _graphicalWindow.getWindow().clear(sf::Color(sf::Color::Black));

    _graphicalWindow.getWindow().setView(_view);

    auto &assetManager = factorio::AssetManager::getInstance();

    sf::Texture &waterTexture = assetManager.getTexture("water");
    sf::Texture &sandTexture = assetManager.getTexture("sand");
    sf::Texture &grassTexture = assetManager.getTexture("grass");
    sf::Texture &ironTexture = assetManager.getTexture("iron");
    sf::Texture &copperTexture = assetManager.getTexture("copper");

    sf::Sprite waterSprite(waterTexture);
    sf::Sprite sandSprite(sandTexture);
    sf::Sprite grassSprite(grassTexture);
    sf::Sprite ironSprite(ironTexture);
    sf::Sprite copperSprite(copperTexture);

    waterSprite.setScale(0.5f, 0.5f);
    sandSprite.setScale(0.5f, 0.5f);
    grassSprite.setScale(0.5f, 0.5f);
    ironSprite.setScale(0.5f, 0.5f);
    copperSprite.setScale(0.5f, 0.5f);

    int TILE_SIZE = 16;

    for (const auto& tile : _mapGenerator.world.tiles) {
        switch (tile.groundType)
        {
        case 0:
            waterSprite.setPosition(tile.x * TILE_SIZE, tile.y * TILE_SIZE);
            _graphicalWindow.getWindow().draw(waterSprite);
            break;
        case 1:
            sandSprite.setPosition(tile.x * TILE_SIZE, tile.y * TILE_SIZE);
            _graphicalWindow.getWindow().draw(sandSprite);
            break;
        case 2:
            grassSprite.setPosition(tile.x * TILE_SIZE, tile.y * TILE_SIZE);
            _graphicalWindow.getWindow().draw(grassSprite);
            break;
        default:
            break;
        }

        switch (tile.resourceType)
        {
        case 1:
            ironSprite.setPosition(tile.x * TILE_SIZE, tile.y * TILE_SIZE);
            _graphicalWindow.getWindow().draw(ironSprite);
            break;
        case 2:
            copperSprite.setPosition(tile.x * TILE_SIZE, tile.y * TILE_SIZE);
            _graphicalWindow.getWindow().draw(copperSprite);
            break;
        default:
            break;
        }
    }

    // ImGui
    ImGui::SFML::Render(_graphicalWindow.getWindow());

    _graphicalWindow.getWindow().display();
}