#pragma once

#include <SFML/Window.hpp>

#include <engine/ecs/System.hpp>
#include <engine/ecs/Components.hpp>

#include "config/EcsConfig.hpp"
#include "Components.hpp"

namespace rtype
{
    namespace system
    {
        /**
         * @brief CubeSprite system class to draw a cube sprite
         * 
         */
        class CubeSpriteSystem : public engine::ecs::System<rtype::config::ComponentCount, rtype::config::SystemCount>
        {
        public:
            /**
             * @brief Construct a new CubeSprite System object
             * 
             * @param entityManager 
             */
            CubeSpriteSystem(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &entityManager) : _entityManager(entityManager)
            {
                setRequirements<
                    engine::ecs::components::Transform,
                    engine::ecs::components::CubeSprite>();
            }

            /**
             * @brief Draw the CubeSprite System object
             * 
             * @param window 
             */
            void draw(sf::RenderWindow &window)
            {
                for (const auto &entity : getManagedEntities())
                {
                    auto [transform, sprite] = _entityManager.getComponents<
                        engine::ecs::components::Transform,
                        engine::ecs::components::CubeSprite>(entity);

                    sf::RectangleShape rectangle(sf::Vector2f(100, 100));
                    rectangle.setFillColor(sprite.color);
                    rectangle.setPosition(sf::Vector2f(transform.x, transform.y));

                    window.draw(rectangle);
                }
            }

        private:
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &_entityManager;
        };
    }
}