#pragma once

#include <engine/ecs/System.hpp>
#include <engine/ecs/Components.hpp>

#include "config/EcsConfig.hpp"
#include "Components.hpp"
#include "EntityTemplate.hpp"

namespace rtype
{
    namespace system
    {
        /**
         * @brief Clean entity system class to remove entities
         * 
         */
        class SpawnBonusSystem : public engine::ecs::System<rtype::config::ComponentCount, rtype::config::SystemCount>
        {
        public:
            /**
             * @brief Construct a new Clean Entity System object
             * 
             * @param entityManager 
             */
            SpawnBonusSystem(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& entityManager) : _id(0), _entityManager(entityManager), _entityTemplate(_entityManager)
            {
                setRequirements<
                    rtype::ecs::components::State,
                    rtype::ecs::components::EnnemiId,
                    engine::ecs::components::Transform
                >();
            }

            /**
             * @brief Update the Spawn Bonus System object
             * 
             * @param dt 
             */
            void update(const float dt)
            {
                std::srand(std::time(nullptr));
                int nb = 0 + ( std::rand() % ( 100 - 0 + 1 ));

                for (const auto& entity : getManagedEntities())
                {
                    auto [state, transform] = _entityManager.getComponents<
                        rtype::ecs::components::State,
                        engine::ecs::components::Transform
                    >(entity);

                    if (state.toRemove == false) {
                        continue;
                    }
                    if (nb % 10 == 0) {
                        _entityTemplate.createHealthBonus(transform.x, transform.y, _id++);
                    }
                    if (nb % 25 == 0) {
                        _entityTemplate.createSpecialShootBonus(transform.x, transform.y, _id++);
                    }
                }
            }

        private:
            int _id;
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& _entityManager;
            rtype::EntityTemplate _entityTemplate;
        };
    }
}