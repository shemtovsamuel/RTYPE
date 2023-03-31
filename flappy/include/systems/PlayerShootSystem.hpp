#pragma once

#include <engine/ecs/System.hpp>
#include <engine/ecs/Components.hpp>

#include "config/EcsConfig.hpp"
#include "Components.hpp"
#include "events/inputEvent.hpp"
#include "systems/SpriteSystem.hpp"
#include "systems/SpriteAnimationSystem.hpp"
#include "AssetManager.hpp"
#include "EntityTemplate.hpp"
#include <chrono>
#include <SFML/Audio.hpp>

namespace rtype
{
    namespace system
    {
        /**
         * @brief PlayerShoot system class used to let the player shoot.
         *
         */
        class PlayerShootSystem : public engine::ecs::System<rtype::config::ComponentCount, rtype::config::SystemCount>
        {
        public:
            /**
             * @brief Construct a new Player Shoot System object
             *
             * @param entityManager
             */
            PlayerShootSystem(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &entityManager) : _entityManager(entityManager), _lastShotTime(std::chrono::high_resolution_clock::now()), _assetManager(rtype::AssetManager::getInstance()), _entityTemplate(_entityManager, _assetManager)
            {
                setRequirements<
                    engine::ecs::components::Transform,
                    rtype::ecs::components::PlayerShoot>();
            }

            /**
             * @brief Handle the events of the Player Shoot System object
             *
             * @param event
             */
            void handleEvent(const engine::Event &event)
            {
                if (const auto inputEvent = dynamic_cast<const rtype::event::InputEvent *>(&event))
                {
                    if (inputEvent->key != sf::Keyboard::Key::Space)
                        return;

                    auto currentTime = std::chrono::high_resolution_clock::now();
                    auto timeSinceLastShot = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _lastShotTime);
                    if (timeSinceLastShot.count() < 400)
                        return;

                    _lastShotTime = currentTime;
                    for (const auto &entity : getManagedEntities())
                    {
                        auto [transform, shoot] = _entityManager.getComponents<
                            engine::ecs::components::Transform,
                            rtype::ecs::components::PlayerShoot>(entity);

                        _entityTemplate.createPlayerBullet(transform.x, transform.y);
                    }
                }
            }

        private:
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &_entityManager;
            std::chrono::time_point<std::chrono::high_resolution_clock> _lastShotTime;
            rtype::AssetManager &_assetManager;
            rtype::EntityTemplate _entityTemplate;
        };
    }
}