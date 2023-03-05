#pragma once

#include <engine/ecs/System.hpp>
#include <engine/ecs/Components.hpp>

#include "config/EcsConfig.hpp"
#include "Components.hpp"

namespace rtype
{
    namespace system
    {
        /**
         * @brief Collision system class to check collision between entities
         * 
         */
        class CollisionSystem : public engine::ecs::System<rtype::config::ComponentCount, rtype::config::SystemCount>
        {
        public:
            /**
             * @brief Construct a new Collision System object
             * 
             * @param entityManager 
             */
            CollisionSystem(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& entityManager) : _entityManager(entityManager)
            {
                setRequirements<
                    engine::ecs::components::Transform,
                    engine::ecs::components::Hitbox
                >();
            }

            /**
             * @brief Update the Collision System object
             * 
             * @param dt 
             */
            void update(const float dt)
            {
                for (const auto& entity : getManagedEntities())
                {
                    auto &hitbox = _entityManager.getComponent<engine::ecs::components::Hitbox>(entity);

                    hitbox.collided = false;
                }

                for (const auto& entity1 : getManagedEntities())
                {
                    auto [transform1, hitbox1] = _entityManager.getComponents<
                        engine::ecs::components::Transform,
                        engine::ecs::components::Hitbox
                    >(entity1);

                    for (const auto& entity2 : getManagedEntities())
                    {
                        if (entity1 == entity2)
                        {
                            continue;
                        }

                        auto [transform2, hitbox2] = _entityManager.getComponents<
                            engine::ecs::components::Transform,
                            engine::ecs::components::Hitbox
                        >(entity2);

                        if (transform1.x < transform2.x + hitbox2.width &&
                            transform1.x + hitbox1.width > transform2.x &&
                            transform1.y < transform2.y + hitbox2.height &&
                            transform1.y + hitbox1.height > transform2.y)
                        {
                            if (hitbox1.isTrigger || hitbox1.triggerTags.find(hitbox2.tag) != std::string::npos) {
                                hitbox1.collided = false;
                            } else {
                                hitbox1.collided = true;
                            }
                            if (hitbox2.isTrigger || hitbox2.triggerTags.find(hitbox1.tag) != std::string::npos) {
                                hitbox2.collided = false;
                            } else {
                                hitbox2.collided = true;
                            }

                            // TODO MOVE THIS SOMEWHERE ELSE
                            if (hitbox1.tag == "Player" && hitbox2.tag == "Enemy") {
                                auto &playerHealth = _entityManager.getComponent<rtype::ecs::components::Health>(entity1);
                                playerHealth.hp -= 5;
                            } else if (hitbox1.tag == "PlayerBullet" && hitbox2.tag == "Enemy") {
                                auto &enemyHealth = _entityManager.getComponent<rtype::ecs::components::Health>(entity2);
                                enemyHealth.hp -= 5;

                                auto &bulletState = _entityManager.getComponent<rtype::ecs::components::State>(entity1);
                                bulletState.toRemove = true;
                            } else if (hitbox1.tag == "Player" && hitbox2.tag == "Bonus") {
                                auto &bonusState = _entityManager.getComponent<rtype::ecs::components::State>(entity2);

                                bonusState.toRemove = true;
                            }
                        }
                    }
                }
            }

        private:
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& _entityManager;
        };
    }
}