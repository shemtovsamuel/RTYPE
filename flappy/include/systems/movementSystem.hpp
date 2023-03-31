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
                    rtype::ecs::components::MoveComponent>();
            }

            /**
             * @brief Handle the events of the Movement System object
             *
             * @param event
             */

            void handleEvent(const engine::Event &event)
            {
                static sf::Clock clock;
                static bool isJumping = false;
                static float jumpTime = 0.0f;
                static const float GRAVITY = 2000.0f;

                if (const auto inputEvent = dynamic_cast<const rtype::event::InputEvent *>(&event))
                {
                    for (const auto &entity : getManagedEntities())
                    {
                        auto [transform, velocity, move] = _entityManager.getComponents<
                            engine::ecs::components::Transform,
                            engine::ecs::components::Velocity,
                            rtype::ecs::components::MoveComponent>(entity);

                        if (inputEvent->key == sf::Keyboard::Key::Space && !isJumping && clock.getElapsedTime().asSeconds() >= 0.2f)
                        {
                            velocity.y = -700.0f;
                            isJumping = true;
                            jumpTime = 0.0f;
                            clock.restart();
                        }
                        else if (inputEvent->key == sf::Keyboard::Key::Down)
                        {
                            velocity.y = 250.0f;
                        }

                        if (isJumping)
                        {
                            jumpTime = clock.getElapsedTime().asSeconds();
                            velocity.y = -700.0f + GRAVITY * jumpTime;

                            if (velocity.y >= 500.0f)
                            {
                                velocity.y = 500.0f;
                            }

                            if (jumpTime >= 0.5f)
                            {
                                isJumping = false;
                                velocity.y = 500.0f;
                            }
                        }
                        else
                        {
                            velocity.y = GRAVITY * clock.getElapsedTime().asSeconds();

                            if (velocity.y >= 500.0f)
                            {
                                velocity.y = 500.0f;
                            }
                        }
                    }
                }
            }

        private:
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &_entityManager;
        };
    }
}