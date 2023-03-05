#include "Game.hpp"

rtype::Game::Game(asio::io_context& io_context)
	: _context(io_context), _socket(io_context), _endpoint(),
	_isPlayerConnected(false), _window(sf::VideoMode(1920, 1080), "R-Type"), _assetManager(rtype::AssetManager::getInstance()), _entityTemplate(_entityManager, _assetManager),
	_fps(0), _event(), _playerId(0), _serverIp("127.0.0.1"), _inputServerIp("127.0.0.1"), _sentInactive(false)
{
	_lua.open_libraries(sol::lib::base);

	(void)ImGui::SFML::Init(_window);

	// Limit Fps
	_window.setFramerateLimit(60);

	// Entities
	_entityManager.reserve(std::size_t(rtype::config::EntitiesCount));

	// Engine components
	_entityManager.registerComponent<engine::ecs::components::CubeSprite>();
	_entityManager.registerComponent<engine::ecs::components::Transform>();
	_entityManager.registerComponent<engine::ecs::components::Velocity>();
	_entityManager.registerComponent<engine::ecs::components::CubeSprite>();
	_entityManager.registerComponent<engine::ecs::components::SpriteComponent>();
	_entityManager.registerComponent<engine::ecs::components::SpriteAnimation>();
	_entityManager.registerComponent<engine::ecs::components::Hitbox>();

	// Rtype components
	_entityManager.registerComponent<rtype::ecs::components::MoveComponent>();
	_entityManager.registerComponent<rtype::ecs::components::PlayerShoot>();
	_entityManager.registerComponent<rtype::ecs::components::PlayerId>();
	_entityManager.registerComponent<rtype::ecs::components::Health>();
	_entityManager.registerComponent<rtype::ecs::components::State>();
	_entityManager.registerComponent<rtype::ecs::components::Parallax>();

	// Systems
	_entityManager.createSystem<rtype::system::TransformSystem>(_entityManager);
	_entityManager.createSystem<rtype::system::CubeSpriteSystem>(_entityManager);
	_entityManager.createSystem<rtype::system::MovementSystem>(_entityManager);
	_entityManager.createSystem<rtype::system::SpriteSystem>(_entityManager);
	_entityManager.createSystem<rtype::system::SpriteAnimationSystem>(_entityManager);
	_entityManager.createSystem<rtype::system::PlayerShootSystem>(_entityManager);
	_entityManager.createSystem<rtype::system::CollisionSystem>(_entityManager);
	_entityManager.createSystem<rtype::system::HealthSystem>(_entityManager);
	_entityManager.createSystem<rtype::system::ParallaxSystem>(_entityManager);

	// This System need to be the last one added !
	_entityManager.createSystem<rtype::system::CleanEntitySystem>(_entityManager);

	_entityTemplate.createParallax(0.0f, 0.0f, "background", 0.0f, 0);
	_entityTemplate.createParallax(0.0f, 0.0f, "stars", -10.0f, 1);
	_entityTemplate.createParallax(3840.0f, 0.0f, "stars", -10.0f, 2);
	_entityTemplate.createParallax(0.0f, 0.0f, "stones", -20.0f, 3);
	_entityTemplate.createParallax(3840.0f, 0.0f, "stones", -20.0f, 4);
	_entityTemplate.createParallax(0.0f, 0.0f, "planet2", -40.0f, 5);
	_entityTemplate.createParallax(3840.0f, 0.0f, "planet2", -40.0f, 6);
	_entityTemplate.createParallax(0.0f, 0.0f, "planet1", -100.0f, 7);
	_entityTemplate.createParallax(3840.0f, 0.0f, "planet1", -100.0f, 8);
}

rtype::Game::~Game()
{
	ImGui::SFML::Shutdown();
}

void rtype::Game::receive()
{
	_socket.async_receive_from(
		asio::buffer(&_event, sizeof _event), _sender_endpoint,
		[this](const asio::error_code &error, size_t size)
		{
			if (!error && size == sizeof _event)
			{
				handleEvent();
			}
			receive();
		});
}

void rtype::Game::handleEvent()
{
	auto &logger = engine::debug::Logger::getInstance();

	logger.Info("Event received of type : %d", _event.type);

	// generate randomws coords for enemy spawn
	int minX = 1920;
	int maxX = 3840;
	int minY = 0;
	int maxY = 1080 - 161;
	int max_enemy = 10;
	
	int x = minX + ( std::rand() % ( maxX - minX + 1 ));
	int y = minY + ( std::rand() % ( maxY - minY + 1 ));
	int bonusX = minX + ( std::rand() % ( maxX - minX + 1 ));
	int bonusY = minY + ( std::rand() % ( maxY - minY + 1 ));

	switch (_event.type)
	{
	case CONNECT:
		logger.Info("Connected ! Your Player id : %d", _event.id);
		_isPlayerConnected = true;
		_playerId = _event.id;
		_entityTemplate.createPlayer(_playerId, true);
		for (int i = 0; i < max_enemy; i++)
		{
			int id = _entityTemplate.createEnemy(x, y);
			_entityTemplate.createBonus(bonusX, bonusY);

			bonusX = x + ( std::rand() % ( maxX - minX + 1 ));
			bonusY = y + ( std::rand() % ( maxY - minY + 1 ));
			x = minX + ( std::rand() % ( maxX - minX + 1 ));
			y = minY + ( std::rand() % ( maxY - minY + 1 ));

			for (int j = id; j < rtype::config::EntitiesCount; j++) {
				
				auto &transform = _entityManager.getComponent<engine::ecs::components::Transform>(j);

				if ((x >= transform.x && x <= transform.x + 161) &&
				(y >= transform.y && y <= transform.y + 205)) {
					logger.Info("1 --- Enemy %d current position : x : %d y : %d\n\n", id, x, y);
					logger.Info("2 --- Enemy %d checked current position : x : %.0f y : %.0f", j, transform.x, transform.y);
					logger.Info("3 --- Enemy %d collapse with %d", id, j);
					logger.Info("4 --- Before Diff x : %d Diff y : %d", (int)abs(x - transform.x), (int)abs(y - transform.y));
					x = minX + ( std::rand() % ( maxX - minX + 1 ));
					y = minY + ( std::rand() % ( maxY - minY + 1 ));
					logger.Info("5 --- Enemy %d new position : x : %d y : %d", id, x, y);
					logger.Info("6 --- After Diff x : %d Diff y : %d", (int)abs(x - transform.x), (int)abs(y - transform.y));
					j = id;
				}
			}
			logger.Info("--- Enemy %d : OK !", id, x, y);
		}

		break;
	case NEWPLAYER:
		logger.Info("New player connected to the server ! New player id : %d", _event.id);
		_entityTemplate.createPlayer(_event.id, false);
		break;
	case MOVE:
		rtype::event::InputEvent inputEvent = rtype::event::InputEvent();
		inputEvent.playerId = _event.id;
		inputEvent.key = _event.data;
		_entityManager.dispatchEvent(inputEvent);
		break;
	}
}

void rtype::Game::gameLoop()
{
	while (_window.isOpen())
	{
		_context.poll();

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
	while (_window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);

		if (event.type == sf::Event::Closed)
			_window.close();

		if (!_isPlayerConnected) continue;

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

	if (_isPlayerConnected == false) return;

	// Send Keys Events
	for (auto &key : _keysPressed)
	{
		rtype::event::InputEvent inputEvent = rtype::event::InputEvent();
		inputEvent.playerId = _playerId;
		inputEvent.key = key;
		_entityManager.dispatchEvent(inputEvent);
		NetworkEvent event = {MOVE, _playerId, key};
		send<NetworkEvent>(event);
		_sentInactive = false;
	}
	if (_keysPressed.size() == 0)
	{
		rtype::event::InputEvent inputEvent = rtype::event::InputEvent();
		inputEvent.playerId = _playerId;
		inputEvent.key = -1;
		_entityManager.dispatchEvent(inputEvent);
		if (_sentInactive == false) {
			NetworkEvent event = { MOVE, _playerId, -1 };
			send<NetworkEvent>(event);
			_sentInactive = true;
		}
	}
}

void rtype::Game::gameUpdate()
{
	if (!_isPlayerConnected) return;
	_entityManager.updateSystems(_dt.asSeconds());
}

void rtype::Game::gameUi()
{
	ImGui::SFML::Update(_window, _dt);

	if (!_isPlayerConnected) {
		ImGui::Begin("Login");

		ImGui::Text("Ip of the server");

		ImGui::InputText("##_serverIp", _inputServerIp, CHAR_MAX);

		if (ImGui::Button("Login")) {
			_endpoint = asio::ip::udp::endpoint(asio::ip::address::from_string(std::string(_inputServerIp)), 2001);
			_socket.open(asio::ip::udp::v4());
			NetworkEvent connect_event = { CONNECT };
			send<NetworkEvent>(connect_event);
			_context.reset();
			_context.restart();
			receive();
		}

		ImGui::End();
	}

	auto& logger = engine::debug::Logger::getInstance();
	logger.DrawLogWindow();

	ImGui::Begin("Debug");

	ImGui::Text("%s", std::string("Fps : ").append(std::to_string(_fps)).c_str());

	ImGui::End();
}

void rtype::Game::gameDraw()
{
	_window.clear(sf::Color(sf::Color::Black));

	_entityManager.drawSystems(_window);

	ImGui::SFML::Render(_window);

	_window.display();
}