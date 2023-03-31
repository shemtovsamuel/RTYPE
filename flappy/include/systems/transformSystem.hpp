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
         * @brief TransformSystem class used to update the position of the entities.
         * 
         */
        class TransformSystem : public engine::ecs::System<rtype::config::ComponentCount, rtype::config::SystemCount>
        {
        public:
            /**
             * @brief Construct a new Transform System object
             * 
             * @param entityManager 
             */
            TransformSystem(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& entityManager) : _entityManager(entityManager)
            {
                setRequirements<
                    engine::ecs::components::Transform,
                    engine::ecs::components::Velocity
                >();
            }

            /**
             * @brief Update the Transform System object
             * 
             * @param dt 
             */
            void update(const float dt)
            {
                for (const auto& entity : getManagedEntities())
                {
                    auto [transform, velocity] = _entityManager.getComponents<
                        engine::ecs::components::Transform,
                        engine::ecs::components::Velocity
                    >(entity);

                    if (_entityManager.hasComponent<engine::ecs::components::Hitbox>(entity)) {
                        auto &hitbox = _entityManager.getComponent<engine::ecs::components::Hitbox>(entity);
                        if (hitbox.collided) {
                            transform.x = transform.prevX;
                            transform.y = transform.prevY;
                            continue;
                        }
                        transform.prevX = transform.x;
                        transform.prevY = transform.y;

                        transform.x += velocity.x * dt;
                        transform.y += velocity.y * dt;
                    }
                    else {
                        transform.prevX = transform.x;
                        transform.prevY = transform.y;

                        transform.x += velocity.x * dt;
                        transform.y += velocity.y * dt;
                    }
                }
            }

        private:
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& _entityManager;
        };
    }
}