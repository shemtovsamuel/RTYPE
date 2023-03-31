#include "ServerGame.hpp"

rtype::ServerGame::ServerGame() : Game(), _entityTemplate(_entityManager), _levelManager(_entityManager), _scoreManager(_entityManager)
{
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

    // Systems
    _entityManager.createSystem<rtype::system::TransformSystem>(_entityManager);
    _entityManager.createSystem<rtype::system::MovementSystem>(_entityManager);
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
    _entityManager.createSystem<rtype::system::LevelSystem>(_entityManager, _levelManager);
    _entityManager.createSystem<rtype::system::ScoreSystem>(_entityManager, _scoreManager);
    _entityManager.createSystem<rtype::system::SpawnBonusSystem>(_entityManager);

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

void rtype::ServerGame::gameLoop()
{
    _dt = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - _clockStarting).count()) / 1000000;
    _clockStarting = std::chrono::steady_clock::now();
    gameEvent();
    gameUpdate();
}

void rtype::ServerGame::gameUpdate()
{
    if (_players.empty())
        return;
    _entityManager.updateSystems(_dt);
}

bool rtype::ServerGame::isOver()
{
    return false;
}

float rtype::ServerGame::getFps() const
{
    return -1;
}

void rtype::ServerGame::handleEvent(rtype::NetworkEvent content)
{
    switch (content.type) {
        case CONNECT:
            _players[content.id] = _entityTemplate.createPlayer(content.id,
                    true, content.pos);
            break;
        case DIE:
            for (int i = 0; i < rtype::config::EntitiesCount; i++) {
                if (_entityManager.hasComponent<rtype::ecs::components::PlayerId>(
                        i) ||
                        _entityManager.hasComponent<rtype::ecs::components::EnnemiId>(
                                i)) {
                    _entityManager.removeEntity(i);
                }
            }
            if (_players.find(content.id) != _players.end())
                _players.erase(content.id);
            break;
        case INPUT:
            rtype::event::InputEvent inputEvent = rtype::event::InputEvent();
            inputEvent.playerId = content.id;
            inputEvent.key = content.key;
            _entityManager.dispatchEvent(inputEvent);
            break;
    }
}