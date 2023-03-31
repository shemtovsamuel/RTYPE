#include "Game.hpp"
#include "debug/Debugger.hpp"

rtype::Game::Game()
	: _graphicalWindow(), _assetManager(rtype::AssetManager::getInstance()), _entityTemplate(_entityManager, _assetManager),
	  _fps(0)
{
	_lua.open_libraries(sol::lib::base);

	(void)ImGui::SFML::Init(_graphicalWindow.getWindow());

	// Limit Fps
	_graphicalWindow.getWindow().setFramerateLimit(60);

	// Entities
	_entityManager.reserve(std::size_t(rtype::config::EntitiesCount));

	// Engine components
	_entityManager.registerComponent<engine::ecs::components::Transform>();
	_entityManager.registerComponent<engine::ecs::components::Velocity>();
	_entityManager.registerComponent<engine::ecs::components::Hitbox>();

	// Rtype components
	_entityManager.registerComponent<rtype::ecs::components::Sprite>();
	_entityManager.registerComponent<rtype::ecs::components::SpriteAnimation>();
	_entityManager.registerComponent<rtype::ecs::components::MoveComponent>();
	_entityManager.registerComponent<rtype::ecs::components::PlayerShoot>();
	_entityManager.registerComponent<rtype::ecs::components::Health>();
	_entityManager.registerComponent<rtype::ecs::components::State>();
	_entityManager.registerComponent<rtype::ecs::components::Parallax>();
	_entityManager.registerComponent<rtype::ecs::components::DebugTag>();
	_entityManager.registerComponent<rtype::ecs::components::Obstacle>();

	// Systems
	_entityManager.createSystem<rtype::system::TransformSystem>(_entityManager);
	_entityManager.createSystem<rtype::system::MovementSystem>(_entityManager);
	_entityManager.createSystem<rtype::system::SpriteSystem>(_entityManager);
	_entityManager.createSystem<rtype::system::SpriteAnimationSystem>(_entityManager);
	_entityManager.createSystem<rtype::system::CollisionSystem>(_entityManager);
	_entityManager.createSystem<rtype::system::HealthSystem>(_entityManager);
	_entityManager.createSystem<rtype::system::ParallaxSystem>(_entityManager);
	_entityManager.createSystem<rtype::system::ObstacleSystem>(_entityManager);

	// This System need to be the last one added !
	_entityManager.createSystem<rtype::system::CleanEntitySystem>(_entityManager);

	_entityTemplate.createParallax(0.0f, 0.0f, "backgroundFlappy", 0.0f, 0);
	_entityTemplate.createParallax(0.0f, 0.0f, "cloud", -10.0f, 1);
	_entityTemplate.createParallax(3840.0f, 0.0f, "cloud", -10.0f, 2);
	_entityTemplate.createParallax(0.0f, 0.0f, "building", -20.0f, 3);
	_entityTemplate.createParallax(3840.0f, 0.0f, "building", -20.0f, 4);
	_entityTemplate.createParallax(0.0f, 0.0f, "bush", -40.0f, 5);
	_entityTemplate.createParallax(3840.0f, 0.0f, "bush", -40.0f, 6);
	_entityTemplate.createParallax(0.0f, 0.0f, "ground", -100.0f, 7);
	_entityTemplate.createParallax(3840.0f, 0.0f, "ground", -100.0f, 8);

	auto bird = _entityTemplate.createBird();

	_entityTemplate.createObstacle1();
	_entityTemplate.createObstacle2();
	_entityTemplate.createObstacle3();
}

rtype::Game::~Game()
{
	ImGui::SFML::Shutdown();
}

float rtype::Game::getFps() const
{
	return _fps;
}

void rtype::Game::gameLoop()
{
	while (_graphicalWindow.getWindow().isOpen())
	{
		_dt = _dtClock.restart();
		_fps = 1.0f / _dt.asSeconds();
		gameEvent();
		gameUpdate();
		gameUi();
		gameDraw();
	}
}

void rtype::Game::gameEvent()
{
	// Event
	sf::Event event;
	while (_graphicalWindow.getWindow().pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);

		if (event.type == sf::Event::Closed)
			_graphicalWindow.getWindow().close();

		// delete entities out of screen
		for (int i = 0; i < rtype::config::EntitiesCount; i++)
		{
			if (_entityManager.hasComponent<engine::ecs::components::Transform>(i))
			{
				auto transform = _entityManager.getComponent<engine::ecs::components::Transform>(i);

				if (transform.x > 3840)
				{
					std::cout << "Entity " << i << " deleted" << std::endl;
					_entityManager.removeEntity(i);
				}
			}
		}

		for (auto key : _keysToCheck)
		{
			if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key)))
			{
				_keysPressed.insert(key);
			}
			else if (_keysPressed.find(key) != _keysPressed.end())
			{
				_keysPressed.erase(key);
			}
		}
	}

	// Send Keys Events
	for (auto &key : _keysPressed)
	{
		rtype::event::InputEvent inputEvent = rtype::event::InputEvent();
		inputEvent.key = key;
		_entityManager.dispatchEvent(inputEvent);
	}
	if (_keysPressed.size() == 0)
	{
		rtype::event::InputEvent inputEvent = rtype::event::InputEvent();
		inputEvent.key = -1;
		_entityManager.dispatchEvent(inputEvent);
	}
}

void rtype::Game::gameUpdate()
{
	auto &debugger = rtype::debug::Debugger::getInstance();
	debugger.update(*this);

	_entityManager.updateSystems(_dt.asSeconds());
}

void rtype::Game::gameUi()
{
	ImGui::SFML::Update(_graphicalWindow.getWindow(), _dt);

	auto &logger = rtype::debug::Logger::getInstance();
	logger.DrawLogWindow();

	auto &debugger = rtype::debug::Debugger::getInstance();
	debugger.draw(*this);
}

void rtype::Game::gameDraw()
{
	_graphicalWindow.getWindow().clear(sf::Color(sf::Color::Black));

	_entityManager.drawSystems(_graphicalWindow);

	ImGui::SFML::Render(_graphicalWindow.getWindow());

	_graphicalWindow.getWindow().display();
}