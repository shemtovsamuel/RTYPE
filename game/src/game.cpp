#include "Game.hpp"
#include "QueueManager.hpp"

rtype::Game::Game() : _clockStarting(std::chrono::steady_clock::now()), _dt(
        0), _entityManager()
{
}

engine::ecs::EntityManager <rtype::config::ComponentCount, rtype::config::SystemCount> &rtype::Game::getEntityManager()
{
    return _entityManager;
}

void rtype::Game::gameEvent()
{
    auto &queueManager = rtype::QueueManager::getInstance();

    // delete entities out of screen
//    for (int i = 0; i < rtype::config::EntitiesCount; i++) {
//        if (_entityManager.hasComponent<engine::ecs::components::Transform>(
//                i) &&
//                !_entityManager.hasComponent<rtype::ecs::components::ParralaxId>(
//                        i)) {
//            auto transform = _entityManager.getComponent<engine::ecs::components::Transform>(
//                    i);
//
//            if (transform.x > 3840 || transform.x < -500 ||
//                    transform.y > 2160 || transform.y < -200) {
//                if (_entityManager.hasComponent<rtype::ecs::components::PlayerId>(
//                        i))
//                    queueManager.pushInQueue((NetworkEvent){DIE,
//                            _entityManager.getComponent<rtype::ecs::components::PlayerId>(
//                                    i).id, -1, std::make_pair(-1, -1), PLAYER});
//                else if (_entityManager.hasComponent<rtype::ecs::components::ParralaxId>(
//                        i))
//                    queueManager.pushInQueue((NetworkEvent){DIE,
//                            _entityManager.getComponent<rtype::ecs::components::ParralaxId>(
//                                    i).id, -1, std::make_pair(-1, -1),
//                            PARRALAX_LAYER});
//                else if (_entityManager.hasComponent<rtype::ecs::components::EnnemiId>(
//                        i)) {
//                    if (_entityManager.hasComponent<rtype::ecs::components::BossAlien>(
//                            i))
//                        queueManager.pushInQueue((NetworkEvent){DIE,
//                                _entityManager.getComponent<rtype::ecs::components::EnnemiId>(
//                                        i).id, -1, std::make_pair(-1, -1),
//                                BOSS_ALIEN});
//                    else if (_entityManager.hasComponent<rtype::ecs::components::BossAlien>(
//                            i))
//                        queueManager.pushInQueue((NetworkEvent){DIE,
//                                _entityManager.getComponent<rtype::ecs::components::EnnemiId>(
//                                        i).id, -1, std::make_pair(-1, -1),
//                                BOSS_HIVE});
//                } else if (_entityManager.hasComponent<rtype::ecs::components::EnemyCrabId>(
//                        i))
//                    queueManager.pushInQueue((NetworkEvent){DIE,
//                            _entityManager.getComponent<rtype::ecs::components::EnemyCrabId>(
//                                    i).id, -1, std::make_pair(-1, -1),
//                            ENEMY_CRAB});
//                else if (_entityManager.hasComponent<rtype::ecs::components::EnemyBeetleId>(
//                        i))
//                    queueManager.pushInQueue((NetworkEvent){DIE,
//                            _entityManager.getComponent<rtype::ecs::components::EnemyBeetleId>(
//                                    i).id, -1, std::make_pair(-1, -1),
//                            ENEMY_BEETLE});
//                _entityManager.removeEntity(i);
//            }
//        }
//    }
}