#include <engine/ecs/Components.hpp>

#include "LevelManager.hpp"

#include "../game/include/QueueManager.hpp"
#include "Components.hpp"
#include "../game/include/Game.hpp"

rtype::LevelManager::LevelManager(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &entityManager) :
        _entityManager(entityManager),_entityTemplate(_entityManager), _level(1), _enemiId(0), _asteroidId(0), _coordX(840.0), _coordY(0.0), _offset(135.0)
{
}

void rtype::LevelManager::createLevel(int level)
{
    std::srand(std::time(nullptr));
    int minX = 1920;
    int maxX = 3840;
    int minY = 100;
    int maxY = 1080 - 150;
    int nb_enemy = 1 + (level * 5);

    std::vector<std::pair<float, float>> coords = {
            {_coordX + _offset, _coordY}, {_coordX + _offset, _coordY + _offset}, {_coordX + _offset, _coordY + (_offset * 2)}, {_coordX + _offset, _coordY + (_offset * 3)}, {_coordX + _offset, _coordY + (_offset * 4)}, {_coordX + _offset, _coordY + (_offset * 5)}, {_coordX + _offset, _coordY + (_offset * 6)}, {_coordX + _offset, _coordY + (_offset * 7)},
            {_coordX + (_offset * 2), _coordY}, {_coordX + (_offset * 2), _coordY + _offset}, {_coordX + (_offset * 2), (_offset * 2)}, {_coordX + (_offset * 2), _coordY + (_offset * 3)}, {_coordX + (_offset * 2), _coordY + (_offset * 4)}, {_coordX + (_offset * 2), _coordY + (_offset * 5)}, {_coordX + (_offset * 2), _coordY + (_offset * 6)}, {_coordX + (_offset * 2), _coordY + (_offset * 7)},
            {_coordX + (_offset * 3), _coordY}, {_coordX + (_offset * 3), _coordY + _offset}, {_coordX + (_offset * 3), _coordY + (_offset * 2)}, {_coordX + (_offset * 3), _coordY + (_offset * 3)}, {_coordX + (_offset * 3), _coordY + (_offset * 4)}, {_coordX + (_offset * 3), _coordY + (_offset * 5)}, {_coordX + (_offset * 3), _coordY + (_offset * 6)}, {_coordX + (_offset * 3), _coordY + (_offset * 7)},
            {_coordX + (_offset * 4), _coordY}, {_coordX + (_offset * 4), _coordY + _offset}, {_coordX + (_offset * 4), _coordY + (_offset * 2)}, {_coordX + (_offset * 4), _coordY + (_offset * 3)}, {_coordX + (_offset * 4), _coordY + (_offset * 4)}, {_coordX + (_offset * 4), _coordY + (_offset * 5)}, {_coordX + (_offset * 4), _coordY + (_offset * 6)}, {_coordX + (_offset * 4), _coordY + (_offset * 7)},
            {_coordX + (_offset * 5), _coordY}, {_coordX + (_offset * 5), _coordY + _offset}, {_coordX + (_offset * 5), _coordY + (_offset * 2)}, {_coordX + (_offset * 5), _coordY + (_offset * 3)}, {_coordX + (_offset * 5), _coordY + (_offset * 4)}, {_coordX + (_offset * 5), _coordY + (_offset * 5)}, {_coordX + (_offset * 5), _coordY + (_offset * 6)}, {_coordX + (_offset * 5), _coordY + (_offset * 7)},
            {_coordX + (_offset * 6), _coordY}, {_coordX + (_offset * 6), _coordY + _offset}, {_coordX + (_offset * 6), _coordY + (_offset * 2)}, {_coordX + (_offset * 6), _coordY + (_offset * 3)}, {_coordX + (_offset * 6), _coordY + (_offset * 4)}, {_coordX + (_offset * 6), _coordY + (_offset * 5)}, {_coordX + (_offset * 6), _coordY + (_offset * 6)}, {_coordX + (_offset * 6), _coordY + (_offset * 7)},
    };

    std::vector<std::pair<float, float>> chosen_coords;
    int enemy_type = (std::rand() % 2) + 1;

    int asteroidX = minX + ( std::rand() % ( maxX - minX + 1 ));
    int asteroidY = minY + ( std::rand() % ( maxY - minY + 1 ));

    if (nb_enemy > 48) {
        nb_enemy = 48;
    }

    for (int i = 0; i < nb_enemy; i++) {

        int random_index = std::rand() % coords.size();
        std::pair<float, float> random_coord = coords[random_index];

        if (std::find(chosen_coords.begin(), chosen_coords.end(), random_coord) != chosen_coords.end()) {
            random_index = std::rand() % coords.size();
            i -= 1;
            continue;
        }
        random_coord = coords[random_index];
        chosen_coords.push_back(random_coord);

        if (enemy_type == 1) {
            auto &queueManager = rtype::QueueManager::getInstance();
            queueManager.pushInQueue((NetworkEvent({OBJECT, _enemiId, -1, std::make_pair(random_coord.first + 24.0, random_coord.second + 25.0), ENEMY_CRAB})));
            _entityTemplate.createEnemyCrab(random_coord.first + 24.0, random_coord.second + 25.0, _enemiId++);
        } else {
            auto &queueManager = rtype::QueueManager::getInstance();
            queueManager.pushInQueue((NetworkEvent({OBJECT, _enemiId, -1, std::make_pair(random_coord.first + 20.0, random_coord.second + 25.0), ENEMY_BEETLE})));
            _entityTemplate.createEnemyBeetle(random_coord.first + 20.0, random_coord.second + 25.0, _enemiId++);
        }
        enemy_type = (std::rand() % 2) + 1;

        if (i % 25 == 0) {
            auto &queueManager = rtype::QueueManager::getInstance();
            queueManager.pushInQueue((NetworkEvent({OBJECT, _asteroidId, -1, std::make_pair(asteroidX, asteroidY), ASTEROID})));
            _entityTemplate.createAsteroid(asteroidX, asteroidY, _asteroidId++);
            asteroidX = minX + ( std::rand() % ( maxX - minX + 1 ));
            asteroidY = minY + ( std::rand() % ( maxY - minY + 1 ));
        }
    }
}

void rtype::LevelManager::createBossLevel(int level)
{
    std::srand(std::time(nullptr));
    int enemy_type = (std::rand() % 2) + 1;

    if (enemy_type == 1) {
        auto &queueManager = rtype::QueueManager::getInstance();
        queueManager.pushInQueue((NetworkEvent({OBJECT, _enemiId, -1, std::make_pair(1320, 150), BOSS_ALIEN})));
        _entityTemplate.createBossAlien(1320, 150, _enemiId++);
    } else {
        auto &queueManager = rtype::QueueManager::getInstance();
        queueManager.pushInQueue((NetworkEvent({OBJECT, _enemiId, -1, std::make_pair(1720.0, 520.0), BOSS_HIVE})));
        _entityTemplate.createBossHive(1720.0, 520.0, _enemiId++);
    }
}

int rtype::LevelManager::getLevel() const
{
    return _level;
}

void rtype::LevelManager::setLevel(int level)
{
    _level = level;
}