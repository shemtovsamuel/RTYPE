#pragma once

#include <SFML/Window.hpp>

#include <engine/ecs/System.hpp>
#include <engine/ecs/Components.hpp>

#include <algorithm>

#include "config/EcsConfig.hpp"
#include "Components.hpp"

namespace rtype
{
    namespace system
    {
        /**
         * @brief SpriteSystem class used to draw the sprites of the game.
         * 
         */
        class SpriteSystem : public engine::ecs::System<rtype::config::ComponentCount, rtype::config::SystemCount>
        {
        public:
            /**
             * @brief Construct a new Sprite System object
             * 
             * @param entityManager 
             */
            SpriteSystem(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& entityManager) : _entityManager(entityManager)
            {
                setRequirements<
                    engine::ecs::components::Transform,
                    engine::ecs::components::SpriteComponent
                >();
            }

            /**
             * @brief Draw the sprites
             * 
             * @param window 
             */
            void draw(sf::RenderWindow& window)
            {
                std::vector<engine::ecs::Entity> entities;

                for (const auto& entity : getManagedEntities())
                {
                    entities.push_back(entity);
                }

                std::sort(entities.begin(), entities.end(), [this](const engine::ecs::Entity& a, const engine::ecs::Entity& b) -> bool {
                    auto spriteA = _entityManager.getComponent<engine::ecs::components::SpriteComponent>(a);
                    auto spriteB = _entityManager.getComponent<engine::ecs::components::SpriteComponent>(b);

                    return spriteA.layer < spriteB.layer;
                });

                for (const auto& entity : entities)
                {
                    auto [transform, sprite] = _entityManager.getComponents<
                        engine::ecs::components::Transform,
                        engine::ecs::components::SpriteComponent
                    >(entity);

                    sprite.sprite.setPosition(sf::Vector2(transform.x, transform.y));

                    window.draw(sprite.sprite);
                }
            }

        private:
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& _entityManager;
        };
    }
}