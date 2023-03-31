#pragma once

#include <engine/ecs/System.hpp>
#include <engine/ecs/Components.hpp>

#include "config/EcsConfig.hpp"
#include "Components.hpp"
#include "events/InputEvent.hpp"
#include "EntityTemplate.hpp"
#include <chrono>
#include <SFML/Audio.hpp>
#include <valarray>

#include "../game/include/QueueManager.hpp"

namespace rtype
{
    namespace system
    {
        /**
         * @brief EnemyShoot system class used to let the enemy shoot.
         * 
         */
        class EnemyShootSystem : public engine::ecs::System<rtype::config::ComponentCount, rtype::config::SystemCount>
        {
        public:
        /**
             * @brief Construct a new Enemy Shoot System object
             * 
             * @param entityManager 
             */
            EnemyShootSystem(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &entityManager) : _entityManager(entityManager), _entityTemplate(_entityManager), _lastShotTime(std::chrono::high_resolution_clock::now())
            {
                setRequirements<
                    engine::ecs::components::Transform,
                    rtype::ecs::components::Enemy>();
            }

            /**
             * @brief Update the Enemy Shoot system class, to allow enemies to shoot
             * 
             * @param dt The Delta Time for the shoot of enemies
             */
            void update(const float dt)
            {
                std::srand(std::time(nullptr));

                int random = std::rand() % 100;

                auto currentTime = std::chrono::high_resolution_clock::now();
                auto timeSinceLastShot = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _lastShotTime);
                if (timeSinceLastShot.count() < 1800)
                    return;

                _lastShotTime = currentTime;

                for (const auto &entity : getManagedEntities())
                {
                    auto [transform, enemy] = _entityManager.getComponents<
                        engine::ecs::components::Transform,
                        rtype::ecs::components::Enemy>(entity);

                    if (random % 10 == 0) {
                        _entityTemplate.createEnemyBullet(transform.x, transform.y);
                    }
                    random = std::rand() % 100;
                }
            }

        private:
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &_entityManager;
            std::chrono::time_point<std::chrono::high_resolution_clock> _lastShotTime;
            rtype::EntityTemplate _entityTemplate;
        };
    }
}