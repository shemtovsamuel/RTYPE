#pragma once

#include <engine/ecs/System.hpp>
#include <engine/ecs/Components.hpp>
#include <engine/debug/Logger.hpp>

#include "config/EcsConfig.hpp"
#include "Components.hpp"

namespace rtype
{
    namespace system
    {
        class CleanEntitySystem : public engine::ecs::System<rtype::config::ComponentCount, rtype::config::SystemCount>
        {
        public:
            CleanEntitySystem(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& entityManager) : _entityManager(entityManager)
            {
                setRequirements<
                    rtype::ecs::components::State
                >();
            }

            void update(const float dt)
            {
                for (const auto& entity : getManagedEntities())
                {
                    auto [state] = _entityManager.getComponents<
                        rtype::ecs::components::State
                    >(entity);

                    if (state.toRemove) {
                        _entityManager.removeEntity(entity);
                    }
                }
            }

        private:
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& _entityManager;
        };
    }
}