#include "ClientGame.hpp"
#include "debug/Debugger.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "../../game/include/QueueManager.hpp"

rtype::ClientGame::ClientGame() : _isPlayerConnected(false), _graphicalWindow(),
        _assetManager(
        rtype::AssetManager::getInstance()), _entityTemplate(
        _entityManager), _fps(0), _playerId(0), _sentInactive(false), _serverIp(
        "127.0.0.1"), _inputServerIp("127.0.0.1"), _layersTexture(
        {"background", "stars", "stars", "stones", "stones", "planet2",
                "planet2", "planet1", "planet1"}), _layersSpeed(
        {0, -10, -10, -20, -20, -40, -40, -100,
                -100})/*, _levelManager(_entityManager), */, _scoreManager(
        _entityManager)
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
    _entityManager.registerComponent<rtype::ecs::components::PlayerId>();
    _entityManager.registerComponent<rtype::ecs::components::ParralaxId>();
    _entityManager.registerComponent<rtype::ecs::components::EnnemiId>();
    _entityManager.registerComponent<rtype::ecs::components::EnemyBeetleId>();
    _entityManager.registerComponent<rtype::ecs::components::EnemyCrabId>();
    _entityManager.registerComponent<rtype::ecs::components::ShootBonusId>();
    _entityManager.registerComponent<rtype::ecs::components::HealthBonusId>();
    _entityManager.registerComponent<rtype::ecs::components::AsteroidId>();
    _entityManager.registerComponent<rtype::ecs::components::Health>();
    _entityManager.registerComponent<rtype::ecs::components::State>();
    _entityManager.registerComponent<rtype::ecs::components::Parallax>();
    _entityManager.registerComponent<rtype::ecs::components::Enemy>();
    _entityManager.registerComponent<rtype::ecs::components::BossAlien>();
    _entityManager.registerComponent<rtype::ecs::components::BossHive>();
    _entityManager.registerComponent<rtype::ecs::components::DebugTag>();
    _entityManager.registerComponent<rtype::ecs::components::ParticleSpawner>();
    _entityManager.registerComponent<rtype::ecs::components::LifeTime>();

    // Systems
    _entityManager.createSystem<rtype::system::TransformSystem>(_entityManager);
    _entityManager.createSystem<rtype::system::MovementSystem>(_entityManager);
    _entityManager.createSystem<rtype::system::SpriteSystem>(_entityManager);
    _entityManager.createSystem<rtype::system::SpriteAnimationSystem>(
            _entityManager);
    _entityManager.createSystem<rtype::system::CollisionSystem>(_entityManager);
    _entityManager.createSystem<rtype::system::PlayerShootSystem>(
            _entityManager);
    _entityManager.createSystem<rtype::system::EnemyShootSystem>(
            _entityManager);
    _entityManager.createSystem<rtype::system::BossHiveShootSystem>(
            _entityManager);
    _entityManager.createSystem<rtype::system::BossAlienShootSystem>(
            _entityManager);

    _entityManager.createSystem<rtype::system::HealthSystem>(_entityManager);
    _entityManager.createSystem<rtype::system::ParallaxSystem>(_entityManager);
    _entityManager.createSystem<rtype::system::ScoreSystem>(_entityManager,
            _scoreManager);
    _entityManager.createSystem<rtype::system::ParticleSystem>(
            _entityManager);
    _entityManager.createSystem<rtype::system::LifeTimeSystem>(_entityManager);

    _entityTemplate.createTopBoundary(0.0f, 0.0f);
    _entityTemplate.createBottomBoundary(0.0f, 1040.0f);

    // This System need to be the last one added !
    _entityManager.createSystem<rtype::system::CleanEntitySystem>(
            _entityManager);

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

rtype::ClientGame::~ClientGame()
{
    ImGui::SFML::Shutdown();
}

float rtype::ClientGame::getFps() const
{
    return _fps;
}

void rtype::ClientGame::handleEvent(rtype::NetworkEvent package)
{
    auto &logger = rtype::debug::Logger::getInstance();

    logger.Info("Event received of type : %d", package.type);

    switch (package.type) {
        case CONNECT:
            if (_players.find(package.id) != _players.end())
                return;
            logger.Info("Connected ! Your Player id : %d", package.id);
            _isPlayerConnected = true;
            _playerId = package.id;
            _players[package.id] = _entityTemplate.createPlayer(_playerId, true,
                    package.pos);
            break;
        case OBJECT:
            handleReceivedObject(package);
            break;
        case UNDEFINED:
            break;
        case DIE:
            die(package);
            break;
        case ENEMY_SHOOT:
            //            _entityTemplate.createEnemyBullet(package.pos.first,
            //                    package.pos.second);
            break;
        case ALIEN_SHOOT:
            //            _entityTemplate.createBossHiveBullet(1550, 470, package.pos.first,
            //                    package.pos.second);
            break;
        case HIVE_SHOOT:
            //            _entityTemplate.createBossAlienBullet(1360, 300, package.pos.first,
            //                    package.pos.second);
            break;
        case INPUT:
            rtype::event::InputEvent inputEvent = rtype::event::InputEvent();
            inputEvent.playerId = package.id;
            inputEvent.key = package.key;
            _entityManager.dispatchEvent(inputEvent);
            break;
    }
}

void rtype::ClientGame::gameLoop()
{
    _dt = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::steady_clock::now() - _clockStarting).count()) /
            1000000;
    _clockStarting = std::chrono::steady_clock::now();
    _fps = 1.0f / _dt;
    gameEvent();
    gameUpdate();
    gameUi();
    gameDraw();
}

void rtype::ClientGame::gameEvent()
{
    auto &queueManager = rtype::QueueManager::getInstance();

    // Event
    sf::Event myEvent{};
    while (_graphicalWindow.getWindow().pollEvent(myEvent)) {
        ImGui::SFML::ProcessEvent(myEvent);

        if (myEvent.type == sf::Event::Closed)
            _graphicalWindow.getWindow().close();

        if (!_isPlayerConnected)
            continue;

        // delete entities out of screen
        for (int i = 0; i < rtype::config::EntitiesCount; i++) {
            if (_entityManager.hasComponent<engine::ecs::components::Transform>(
                    i) &&
                    !_entityManager.hasComponent<rtype::ecs::components::ParralaxId>(
                            i)) {
                auto transform = _entityManager.getComponent<engine::ecs::components::Transform>(
                        i);

                if (transform.x > 3840 || transform.x < -500 ||
                        transform.y > 2160 || transform.y < -200) {
                    _entityManager.removeEntity(i);
                }
            }
        }

        for (auto key: _keysToCheck) {
            if (sf::Keyboard::isKeyPressed(
                    static_cast<sf::Keyboard::Key>(key))) {
                _keysPressed.insert(key);
            } else if (_keysPressed.find(key) != _keysPressed.end()) {
                _keysPressed.erase(key);
            }
        }
    }

    if (!_isPlayerConnected)
        return;

    // Send Keys Events
    for (auto &key: _keysPressed) {
        rtype::event::InputEvent inputEvent = rtype::event::InputEvent();
        inputEvent.playerId = _playerId;
        inputEvent.key = key;
        _entityManager.dispatchEvent(inputEvent);
        NetworkEvent event = {INPUT, _playerId, key, std::make_pair(-1, -1),
                NONE};
        queueManager.pushInQueue(event);
        _sentInactive = false;
    }
    if (_keysPressed.empty()) {
        rtype::event::InputEvent inputEvent = rtype::event::InputEvent();
        inputEvent.playerId = _playerId;
        inputEvent.key = -1;
        _entityManager.dispatchEvent(inputEvent);
        if (!_sentInactive) {
            NetworkEvent event = {INPUT, _playerId, -1, std::make_pair(-1, -1),
                    NONE};
            queueManager.pushInQueue(event);
            _sentInactive = true;
        }
    }
}

void rtype::ClientGame::gameUpdate()
{
    auto &debugger = rtype::debug::Debugger::getInstance();
    debugger.update(*this);

    if (!_isPlayerConnected)
        return;
    _entityManager.updateSystems(_dt);
}

void rtype::ClientGame::gameUi()
{
    auto &queueManager = rtype::QueueManager::getInstance();
    ImGui::SFML::Update(_graphicalWindow.getWindow(), sf::seconds(_dt));

    if (!_isPlayerConnected) {
        ImGui::Begin("Login");

        ImGui::Text("Ip of the server");

        ImGui::InputText("##_serverIp", _inputServerIp, CHAR_MAX);

        if (ImGui::Button("Login")) {
            NetworkEvent connect_event = {CONNECT, -1, -1,
                    std::make_pair(-1, -1), NONE};
            queueManager.pushInQueue(connect_event);
            _isPlayerConnected = true;
        }

        ImGui::End();
    }
    // Debug ici quand on appuie sur O
    auto &logger = rtype::debug::Logger::getInstance();
    logger.DrawLogWindow();

    auto &debugger = rtype::debug::Debugger::getInstance();
    debugger.draw(*this);
}

void rtype::ClientGame::gameDraw()
{
    _graphicalWindow.getWindow().clear(sf::Color(sf::Color::Black));

    _entityManager.drawSystems(_graphicalWindow);

    ImGui::SFML::Render(_graphicalWindow.getWindow());

    _graphicalWindow.getWindow().display();
}

void rtype::ClientGame::handleReceivedObject(rtype::NetworkEvent package)
{
    switch (package.objectType) {
        case PLAYER:
            for (int i = 0; i < rtype::config::EntitiesCount; i++) {
                if (_entityManager.hasComponent<rtype::ecs::components::PlayerId>(
                        i) &&
                        _entityManager.getComponent<rtype::ecs::components::PlayerId>(
                                i).id == package.id) {
                    auto &transform = _entityManager.getComponent<engine::ecs::components::Transform>(
                            i);

                    transform.x = package.pos.first;
                    transform.y = package.pos.second;
                    return;
                }
            }
            _players[package.id] = _entityTemplate.createPlayer(package.id,
                    false, package.pos);
            break;
        case ENEMY_CRAB:
            for (int i = 0; i < rtype::config::EntitiesCount; i++) {
                if (_entityManager.hasComponent<rtype::ecs::components::EnemyCrabId>(
                        i) &&
                        _entityManager.getComponent<rtype::ecs::components::EnemyCrabId>(
                                i).id == package.id) {
                    auto &transform = _entityManager.getComponent<engine::ecs::components::Transform>(
                            i);

                    transform.x = package.pos.first;
                    transform.y = package.pos.second;
                    return;
                }
            }
            _entityTemplate.createEnemyCrab(package.pos.first,
                    package.pos.second, package.id);
            break;
        case ENEMY_BEETLE:
            for (int i = 0; i < rtype::config::EntitiesCount; i++) {
                if (_entityManager.hasComponent<rtype::ecs::components::EnemyBeetleId>(
                        i) &&
                        _entityManager.getComponent<rtype::ecs::components::EnemyBeetleId>(
                                i).id == package.id) {
                    auto &transform = _entityManager.getComponent<engine::ecs::components::Transform>(
                            i);

                    transform.x = package.pos.first;
                    transform.y = package.pos.second;
                    return;
                }
            }
            _entityTemplate.createEnemyBeetle(package.pos.first,
                    package.pos.second, package.id);
            break;
        case BOSS_HIVE:
            for (int i = 0; i < rtype::config::EntitiesCount; i++) {
                if (_entityManager.hasComponent<rtype::ecs::components::EnnemiId>(
                        i) &&
                        _entityManager.getComponent<rtype::ecs::components::EnnemiId>(
                                i).id == package.id) {
                    auto &transform = _entityManager.getComponent<engine::ecs::components::Transform>(
                            i);

                    transform.x = package.pos.first;
                    transform.y = package.pos.second;
                    return;
                }
            }
            _entityTemplate.createBossHive(package.pos.first,
                    package.pos.second, package.id);
            break;
        case BOSS_ALIEN:
            for (int i = 0; i < rtype::config::EntitiesCount; i++) {
                if (_entityManager.hasComponent<rtype::ecs::components::EnnemiId>(
                        i) &&
                        _entityManager.getComponent<rtype::ecs::components::EnnemiId>(
                                i).id == package.id) {
                    auto &transform = _entityManager.getComponent<engine::ecs::components::Transform>(
                            i);

                    transform.x = package.pos.first;
                    transform.y = package.pos.second;
                    return;
                }
            }
            _entityTemplate.createBossAlien(package.pos.first,
                    package.pos.second, package.id);
            break;
        case PARRALAX_LAYER:
            for (int i = 0; i < rtype::config::EntitiesCount; i++) {
                if (_entityManager.hasComponent<rtype::ecs::components::ParralaxId>(
                        i) &&
                        _entityManager.getComponent<rtype::ecs::components::ParralaxId>(
                                i).id == package.id) {
                    auto &transform = _entityManager.getComponent<engine::ecs::components::Transform>(
                            i);

                    transform.x = package.pos.first;
                    transform.prevX = package.pos.first;
                    transform.y = package.pos.second;
                    transform.prevY = package.pos.second;
                    return;
                }
            }
            _entityTemplate.createParallax(package.pos.first,
                    package.pos.second, _layersTexture[package.id],
                    _layersSpeed[package.id], package.id);
            break;
        case HEALTH_BONUS:
            for (int i = 0; i < rtype::config::EntitiesCount; i++) {
                if (_entityManager.hasComponent<rtype::ecs::components::HealthBonusId>(
                        i) &&
                        _entityManager.getComponent<rtype::ecs::components::HealthBonusId>(
                                i).id == package.id) {
                    auto &transform = _entityManager.getComponent<engine::ecs::components::Transform>(
                            i);

                    transform.x = package.pos.first;
                    transform.prevX = package.pos.first;
                    transform.y = package.pos.second;
                    transform.prevY = package.pos.second;
                    return;
                }
            }
            _entityTemplate.createHealthBonus(package.pos.first,
                    package.pos.second, package.id);
            break;
        case SHOOT_BONUS:
            for (int i = 0; i < rtype::config::EntitiesCount; i++) {
                if (_entityManager.hasComponent<rtype::ecs::components::ShootBonusId>(
                        i) &&
                        _entityManager.getComponent<rtype::ecs::components::ShootBonusId>(
                                i).id == package.id) {
                    auto &transform = _entityManager.getComponent<engine::ecs::components::Transform>(
                            i);

                    transform.x = package.pos.first;
                    transform.prevX = package.pos.first;
                    transform.y = package.pos.second;
                    transform.prevY = package.pos.second;
                    return;
                }
            }
            _entityTemplate.createSpecialShootBonus(package.pos.first,
                    package.pos.second, package.id);
            break;
        case ASTEROID:
            for (int i = 0; i < rtype::config::EntitiesCount; i++) {
                if (_entityManager.hasComponent<rtype::ecs::components::AsteroidId>(
                        i) &&
                        _entityManager.getComponent<rtype::ecs::components::AsteroidId>(
                                i).id == package.id) {
                    auto &transform = _entityManager.getComponent<engine::ecs::components::Transform>(
                            i);

                    transform.x = package.pos.first;
                    transform.prevX = package.pos.first;
                    transform.y = package.pos.second;
                    transform.prevY = package.pos.second;
                    return;
                }
            }
            _entityTemplate.createAsteroid(package.pos.first,
                    package.pos.second, package.id);
            break;
    }
}

void rtype::ClientGame::die(rtype::NetworkEvent package)
{
    if (package.id == _playerId && package.objectType == PLAYER)
        _isPlayerConnected = false;
    for (int i = 0; i < rtype::config::EntitiesCount; i++) {
        switch (package.objectType) {
            case PLAYER:
                if (_entityManager.hasComponent<rtype::ecs::components::PlayerId>(
                        i) &&
                        _entityManager.getComponent<rtype::ecs::components::PlayerId>(
                                i).id == package.id) {
                    _entityManager.removeEntity(i);
                    return;
                }
            case ENEMY_BEETLE:
                if (_entityManager.hasComponent<rtype::ecs::components::EnemyBeetleId>(
                        i) &&
                        _entityManager.getComponent<rtype::ecs::components::EnemyBeetleId>(
                                i).id == package.id) {
                    _entityManager.removeEntity(i);
                    return;
                }
            case ENEMY_CRAB:
                if (_entityManager.hasComponent<rtype::ecs::components::EnemyCrabId>(
                        i) &&
                        _entityManager.getComponent<rtype::ecs::components::EnemyCrabId>(
                                i).id == package.id) {
                    _entityManager.removeEntity(i);
                    return;
                }
            case BOSS_ALIEN:
                if (_entityManager.hasComponent<rtype::ecs::components::EnnemiId>(
                        i) &&
                        _entityManager.getComponent<rtype::ecs::components::EnnemiId>(
                                i).id == package.id) {
                    _entityManager.removeEntity(i);
                    return;
                }
            case BOSS_HIVE:
                if (_entityManager.hasComponent<rtype::ecs::components::EnnemiId>(
                        i) &&
                        _entityManager.getComponent<rtype::ecs::components::EnnemiId>(
                                i).id == package.id) {
                    _entityManager.removeEntity(i);
                    return;
                }
        }
    }
    return;
}

bool rtype::ClientGame::isOver()
{
    return !_graphicalWindow.getWindow().isOpen();
}

std::string rtype::ClientGame::getIp()
{
    return std::string(_inputServerIp);
}

int rtype::ClientGame::getPlayerID()
{
    return _playerId;
}
