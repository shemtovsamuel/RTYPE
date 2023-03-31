#pragma once

#include <engine/ecs/System.hpp>
#include <engine/ecs/Components.hpp>

#include "config/EcsConfig.hpp"
#include "Components.hpp"

namespace rtype
{
    namespace system
    {
        class HealthSystem : public engine::ecs::System<rtype::config::ComponentCount, rtype::config::SystemCount>
        {
        public:
            HealthSystem(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& entityManager) : _entityManager(entityManager)
            {
                setRequirements<
                    rtype::ecs::components::Health,
                    rtype::ecs::components::State
                >();
            }

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
                    }
                }
            }

        private:
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& _entityManager;
        };
    }
}