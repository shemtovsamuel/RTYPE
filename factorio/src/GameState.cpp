#include <engine/ecs/Components.hpp>

#include "GameState.hpp"

factorio::GameState::GameState() : _gameInput(), _gameRenderer(),  _debugger(*this), _gameLoop(_gameInput, _gameRenderer, _debugger)
{
    // Ecs
    _entityManager.reserve(std::size_t(factorio::config::EntitiesCount));

    // Engine components
	_entityManager.registerComponent<engine::ecs::components::Transform>();
	_entityManager.registerComponent<engine::ecs::components::Velocity>();
	_entityManager.registerComponent<engine::ecs::components::Hitbox>();

	// Factorio components
	_entityManager.registerComponent<factorio::ecs::components::Sprite>();
	_entityManager.registerComponent<factorio::ecs::components::SpriteAnimation>();

	// Systems
}

factorio::GameState::~GameState()
{
}

engine::ecs::EntityManager<factorio::config::ComponentCount, factorio::config::SystemCount>& factorio::GameState::getEntityManager()
{
    return _entityManager;
}

factorio::GameLoop& factorio::GameState::getGameLoop()
{
    return _gameLoop;
}

factorio::GameRenderer& factorio::GameState::getGameRenderer()
{
    return _gameRenderer;
}

factorio::GameInput& factorio::GameState::getGameInput()
{
    return _gameInput;
}

void factorio::GameState::run()
{
    _gameLoop.run();
}