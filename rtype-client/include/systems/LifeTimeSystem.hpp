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
        class LifeTimeSystem : public engine::ecs::System<rtype::config::ComponentCount, rtype::config::SystemCount>
        {
        public:
            /**
             * @brief Construct a new Collision System object
             *
             * @param entityManager
             */
            LifeTimeSystem(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &entityManager) : _entityManager(entityManager)
            {
                setRequirements<rtype::ecs::components::LifeTime, rtype::ecs::components::State>();
            }

            /**
             * @brief Update the Collision System object
             *
             * @param dt
             */
            void update(const float dt)
            {
                for (const auto &entity : getManagedEntities())
                {
                    auto [lifeTime, state] = _entityManager.getComponents<rtype::ecs::components::LifeTime, rtype::ecs::components::State>(entity);

                    lifeTime.lifeTime -= dt;
                    if (lifeTime.lifeTime <= 0)
                        state.toRemove = true;
                }
            }

        private:
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &_entityManager;
        };
    }
}