#include <imgui.h>
#include <imgui-SFML.h>

#include "debug/Logger.hpp"

#include "GameLoop.hpp"

factorio::GameLoop::GameLoop(factorio::GameInput& gameInput, factorio::GameRenderer& gameRenderer, factorio::debug::Debugger& debugger) : _gameInput(gameInput), _gameRenderer(gameRenderer), _debugger(debugger)
{
}

factorio::GameLoop::~GameLoop()
{
}

float factorio::GameLoop::getFps() const
{
    return 1.0f / _dt.asSeconds();
}

void factorio::GameLoop::run()
{
    while (_gameRenderer.getWindow().isOpen())
    {
        _dt = _dtClock.restart();

        input();
        update();
        render();
    }
}

void factorio::GameLoop::input()
{
    sf::Event event;
	while (_gameRenderer.getWindow().pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);

		if (event.type == sf::Event::Closed)
			_gameRenderer.getWindow().close();

        if (event.type == sf::Event::MouseWheelScrolled)
            _gameRenderer.getView().zoom(1 - event.mouseWheelScroll.delta * 0.1f);
        
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
            _gameRenderer.generateMap();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
            _gameRenderer.getMapGenerator().octaves += 1;
        
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
            _gameRenderer.getMapGenerator().octaves -= 1;

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
            _gameRenderer.getMapGenerator().bias -= 0.1f;

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
            _gameRenderer.getMapGenerator().bias += 0.1f;
	}
}

void factorio::GameLoop::update()
{
    _debugger.update();

    ImGui::SFML::Update(_gameRenderer.getWindow(), _dt);
}

void factorio::GameLoop::render()
{
    auto& logger = factorio::debug::Logger::getInstance();
    logger.DrawLogWindow();

    _debugger.draw();

    _gameRenderer.render();
}