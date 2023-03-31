#pragma once

#include <engine/ecs/System.hpp>
#include <engine/ecs/Components.hpp>

#include "config/EcsConfig.hpp"
#include "Components.hpp"

#include "../game/include/QueueManager.hpp"

namespace rtype
{
    namespace system
    {
        /**
         * @brief Health system class to check if an entity is dead or not
         * 
         */
        class HealthSystem : public engine::ecs::System<rtype::config::ComponentCount, rtype::config::SystemCount>
        {
        public:
            /**
             * @brief Construct a new Health System object
             * 
             * @param entityManager 
             */
            HealthSystem(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& entityManager) : _entityManager(entityManager)
            {
                setRequirements<
                    rtype::ecs::components::Health,
                    rtype::ecs::components::State
                >();
            }

            /**
             * @brief Update the Health System object
             * 
             * @param dt 
             */
            void update(const float dt)
            {
                for (const auto& entity : getManagedEntities())
                {
                    auto [health, state] = _entityManager.getComponents<
                        rtype::ecs::components::Health,
                        rtype::ecs::components::State
                    >(entity);

                    if (health.hp <= 0) {
                        state.toRemove = true;
                        if (_entityManager.hasComponent<ecs::components::PlayerId>(entity)) {
                            auto &queueManager = rtype::QueueManager::getInstance();
                            queueManager.pushInQueue(rtype::NetworkEvent({DIE, _entityManager.getComponent<ecs::components::PlayerId>(entity).id, -1, std::make_pair(-1, -1), PLAYER}));
                        } else if (_entityManager.hasComponent<ecs::components::BossHive>(entity)) {
                            auto &queueManager = rtype::QueueManager::getInstance();
                            queueManager.pushInQueue((rtype::NetworkEvent({DIE, _entityManager.getComponent<ecs::components::EnnemiId>(entity).id, -1, std::make_pair(-1, -1), BOSS_HIVE})));
                        } else if (_entityManager.hasComponent<ecs::components::BossAlien>(entity)) {
                            auto &queueManager = rtype::QueueManager::getInstance();
                            queueManager.pushInQueue((rtype::NetworkEvent({DIE, _entityManager.getComponent<ecs::components::EnnemiId>(entity).id, -1, std::make_pair(-1, -1), BOSS_ALIEN})));
                        } else if (_entityManager.hasComponent<ecs::components::EnemyCrabId>(entity)) {
                            auto &queueManager = rtype::QueueManager::getInstance();
                            queueManager.pushInQueue((rtype::NetworkEvent({DIE, _entityManager.getComponent<ecs::components::EnemyCrabId>(entity).id, -1, std::make_pair(-1, -1), ENEMY_CRAB})));
                        } else if (_entityManager.hasComponent<ecs::components::EnemyBeetleId>(entity)) {
                            auto &queueManager = rtype::QueueManager::getInstance();
                            queueManager.pushInQueue((rtype::NetworkEvent({DIE, _entityManager.getComponent<ecs::components::EnemyBeetleId>(entity).id, -1, std::make_pair(-1, -1), ENEMY_BEETLE})));
                        }
                    }
                }
            }

        private:
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& _entityManager;
        };
    }
}