#pragma once

#include <engine/ecs/System.hpp>
#include <engine/ecs/Components.hpp>

#include "config/EcsConfig.hpp"
#include "Components.hpp"

namespace rtype
{
    namespace system
    {
        class ParallaxSystem : public engine::ecs::System<rtype::config::ComponentCount, rtype::config::SystemCount>
        {
        public:
            ParallaxSystem(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &entityManager) : _entityManager(entityManager)
            {
                setRequirements<
                    engine::ecs::components::Transform,
                    engine::ecs::components::Velocity,
                    rtype::ecs::components::Parallax>();
            }

            void update(const float dt)
            {
                for (const auto &entity : getManagedEntities())
                {
                    auto [transform, velocity, parallax] = _entityManager.getComponents<
                        engine::ecs::components::Transform,
                        engine::ecs::components::Velocity,
                        rtype::ecs::components::Parallax>(entity);

                    if (transform.x <= -parallax.pos)
                    {
                        transform.x = parallax.pos;
                    }
                }
            }

        private:
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &_entityManager;
        };
    }
}