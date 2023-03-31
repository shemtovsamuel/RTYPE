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
         * @brief Clean entity system class to remove entities
         * 
         */
        class CleanEntitySystem : public engine::ecs::System<rtype::config::ComponentCount, rtype::config::SystemCount>
        {
        public:
            /**
             * @brief Construct a new Clean Entity System object
             * 
             * @param entityManager 
             */
            CleanEntitySystem(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& entityManager) : _entityManager(entityManager)
            {
                setRequirements<
                    rtype::ecs::components::State
                >();
            }

            /**
             * @brief Update the Clean Entity System object
             * 
             * @param dt 
             */
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