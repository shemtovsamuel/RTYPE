#pragma once

#include <SFML/Window.hpp>

#include "graphical/GraphicalWindow.hpp"

#include <engine/ecs/System.hpp>
#include <engine/ecs/Components.hpp>

#include <algorithm>

#include "config/EcsConfig.hpp"
#include "Components.hpp"

#include "debug/Debugger.hpp"

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
                    rtype::ecs::components::Sprite
                >();
            }

            /**
             * @brief Draw the sprites
             * 
             * @param window 
             */
            void draw(engine::graphical::GraphicalWindow& window)
            {
                std::vector<engine::ecs::Entity> entities;

                for (const auto& entity : getManagedEntities())
                {
                    entities.push_back(entity);
                }

                std::sort(entities.begin(), entities.end(), [this](const engine::ecs::Entity& a, const engine::ecs::Entity& b) -> bool {
                    auto spriteA = _entityManager.getComponent<rtype::ecs::components::Sprite>(a);
                    auto spriteB = _entityManager.getComponent<rtype::ecs::components::Sprite>(b);

                    return spriteA.layer < spriteB.layer;
                });

                for (const auto& entity : entities)
                {
                    auto [transform, sprite] = _entityManager.getComponents<
                        engine::ecs::components::Transform,
                        rtype::ecs::components::Sprite
                    >(entity);

                    sprite.sprite.setPosition(sf::Vector2(transform.x, transform.y));

                    window.drawSprite(sprite.sprite);

                    auto &debugger = rtype::debug::Debugger::getInstance();

                    if (debugger.getShowHitbox() && _entityManager.hasComponent<engine::ecs::components::Hitbox>(entity)) {
                        sf::RectangleShape rect;
                        rect.setSize(sf::Vector2f(sprite.sprite.getGlobalBounds().width, sprite.sprite.getGlobalBounds().height));
                        rect.setPosition(sf::Vector2f(sprite.sprite.getGlobalBounds().left, sprite.sprite.getGlobalBounds().top));
                        rect.setFillColor(sf::Color::Transparent);
                        rect.setOutlineColor(sf::Color::Red);
                        rect.setOutlineThickness(1);
                        window.drawRect(rect);
                    }
                }
            }

        private:
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& _entityManager;
        };
    }
}