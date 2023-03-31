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
         * @brief ParallaxSystem used to spin the parallax
         * 
         */
        class ParallaxSystem : public engine::ecs::System<rtype::config::ComponentCount, rtype::config::SystemCount>
        {
        public:
            /**
             * @brief Construct a new Parallax System object
             * 
             * @param entityManager 
             */
            ParallaxSystem(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &entityManager) : _entityManager(entityManager)
            {
                setRequirements<
                    engine::ecs::components::Transform,
                    engine::ecs::components::Velocity,
                    rtype::ecs::components::Parallax>();
            }

            /**
             * @brief Update the parallax system so that it spins infinitely
             * 
             * @param dt 
             */
            void update(const float dt)
            {
                for (const auto &entity : getManagedEntities())
                {
                    auto [transform, velocity, parallax] = _entityManager.getComponents<
                        engine::ecs::components::Transform,
                        engine::ecs::components::Velocity,
                        rtype::ecs::components::Parallax>(entity);
                    if (transform.x <= -3840)
                    {
                        transform.x = 3838;
                    }
                }
            }

        private:
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &_entityManager;
        };
    }
}