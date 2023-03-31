#pragma once

#include "ecs/System.hpp"
#include "ecs/Components.hpp"
#include "Components.hpp"
#include "config/EcsConfig.hpp"
#include "events/deathEvent.hpp"

namespace rtype
{
    namespace system
    {
        /*
         * @brief Movement system class used to move the entities
         * 
         */
        class BonusSystem : public engine::ecs::System<rtype::config::ComponentCount, rtype::config::SystemCount>
        {
        public:
            /*
             * @brief Construct a new Movement System object
             * 
             * @param entityManager 
             */
            BonusSystem(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &entityManager) : _entityManager(entityManager)
            {
                setRequirements<
                    engine::ecs::components::Transform,
                    engine::ecs::components::Velocity,
                    rtype::ecs::components::MoveComponent,
                    rtype::ecs::components::BonusComponent>();
            }

            /*
             * @brief Handle the events of the Movement System object
             * 
             * @param event 
             */

            // create a new bonusComponent when an enemyEntity is destroyed

            void handleEvent(const engine::Event &event)
            {
                if (const auto deathEvent = dynamic_cast<const rtype::event::DeathEvent>(&event))
                {
                    if (deathEvent->entityId == 0)
                        return;
                    auto [transform, velocity, moveComponent] = _entityManager.getComponents<
                        engine::ecs::components::Transform,
                        engine::ecs::components::Velocity,
                        rtype::ecs::components::MoveComponent>(deathEvent->entityId);
                    if (transform && velocity && moveComponent)
                    {
                        _entityManager.addComponent<rtype::ecs::components::BonusComponent>(deathEvent->entityId);
                    }
                }
            }

        private:
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &_entityManager;
        };
    }
}