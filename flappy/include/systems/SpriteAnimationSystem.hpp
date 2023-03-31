#pragma once

#include <SFML/Window.hpp>

#include <engine/ecs/System.hpp>
#include <engine/ecs/Components.hpp>

#include "config/EcsConfig.hpp"
#include "Components.hpp"

#include <iostream>

namespace rtype
{
    namespace system
    {
        /**
         * @brief SpriteAnimation system class used to animate sprites
         * 
         */
        class SpriteAnimationSystem : public engine::ecs::System<rtype::config::ComponentCount, rtype::config::SystemCount>
        {
        public:
            /**
             * @brief Construct a new Sprite Animation System object
             * 
             * @param entityManager 
             */
            SpriteAnimationSystem(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& entityManager) : _entityManager(entityManager)
            {
                setRequirements<
                    rtype::ecs::components::Sprite,
                    rtype::ecs::components::SpriteAnimation
                >();
            }

            /**
             * @brief Update the SpriteAnimation system
             * 
             * @param dt 
             */
            void update(const float dt)
            {
                for (const auto& entity : getManagedEntities())
                {
                    auto [sprite, animation] = _entityManager.getComponents<
                        rtype::ecs::components::Sprite,
                        rtype::ecs::components::SpriteAnimation
                    >(entity);

                    animation.accumulatedTime += dt;
                    int frameIndex = static_cast<int>(animation.accumulatedTime / animation.timePerFrame) % animation.frames.size();

                    if (frameIndex != animation.currentFrame)
                    {
                        animation.currentFrame = frameIndex;
                        sprite.sprite.setTextureRect(animation.frames[animation.currentFrame]);
                    }
                }
            }

        private:
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& _entityManager;
        };
    }
}