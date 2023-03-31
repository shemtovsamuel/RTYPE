#pragma once

#include <engine/ecs/System.hpp>
#include <engine/ecs/Components.hpp>

#include "config/EcsConfig.hpp"
#include "Components.hpp"

namespace rtype
{
    namespace system
    {
        class ObstacleSystem : public engine::ecs::System<rtype::config::ComponentCount, rtype::config::SystemCount>
        {
        public:
            ObstacleSystem(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &entityManager) : _entityManager(entityManager)
            {
                setRequirements<
                    rtype::ecs::components::Sprite,
                    engine::ecs::components::Velocity,
                    engine::ecs::components::Transform,
                    engine::ecs::components::Hitbox,
                    rtype::ecs::components::Obstacle>();
            }

            void update(const float dt)
            {
                for (const auto &entity : getManagedEntities())
                {
                    auto [transform, velocity, obstacle] = _entityManager.getComponents<
                        engine::ecs::components::Transform,
                        engine::ecs::components::Velocity,
                        rtype::ecs::components::Obstacle>(entity);
                }
            }

        private:
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &_entityManager;
        };
    }
}