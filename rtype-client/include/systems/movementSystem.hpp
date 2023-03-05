#pragma once

#include <engine/ecs/System.hpp>
#include <engine/ecs/Components.hpp>

#include "config/EcsConfig.hpp"
#include "Components.hpp"
#include "events/inputEvent.hpp"

namespace rtype
{
    namespace system
    {
        /**
         * @brief Movement system class used to move the entities
         * 
         */
        class MovementSystem : public engine::ecs::System<rtype::config::ComponentCount, rtype::config::SystemCount>
        {
        public:
            /**
             * @brief Construct a new Movement System object
             * 
             * @param entityManager 
             */
            MovementSystem(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &entityManager) : _entityManager(entityManager)
            {
                setRequirements<
                    engine::ecs::components::Transform,
                    engine::ecs::components::Velocity,
                    rtype::ecs::components::MoveComponent,
                    rtype::ecs::components::PlayerId>();
            }

            /**
             * @brief Handle the events of the Movement System object
             * 
             * @param event 
             */
            void handleEvent(const engine::Event& event)
            {
                if (const auto inputEvent = dynamic_cast<const rtype::event::InputEvent *>(&event))
                {
                    for (const auto &entity : getManagedEntities())
                    {
                        auto [transform, velocity, move, playerId] = _entityManager.getComponents<
                            engine::ecs::components::Transform,
                            engine::ecs::components::Velocity,
                            rtype::ecs::components::MoveComponent,
                            rtype::ecs::components::PlayerId>(entity);

                        if (playerId.id != inputEvent->playerId)
                            continue;

                        if (inputEvent->key == sf::Keyboard::Key::Left)
                        {
                            velocity.x = -150;
                        }
                        else if (inputEvent->key == sf::Keyboard::Key::Right)
                        {
                            velocity.x = 150;
                        }
                        else if (inputEvent->key == sf::Keyboard::Key::Up)
                        {
                            velocity.y = -150;
                        }
                        else if (inputEvent->key == sf::Keyboard::Key::Down)
                        {
                            velocity.y = 150;
                        }
                        else
                        {
                            velocity.x = 0;
                            velocity.y = 0;
                        }
                    }
                }
            }

        private:
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &_entityManager;
        };
    }
}