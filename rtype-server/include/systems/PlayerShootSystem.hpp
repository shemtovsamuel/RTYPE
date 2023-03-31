#pragma once

#include <engine/ecs/System.hpp>
#include <engine/ecs/Components.hpp>

#include "config/EcsConfig.hpp"
#include "Components.hpp"
#include "events/InputEvent.hpp"
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
            PlayerShootSystem(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &entityManager) : _entityManager(entityManager), _lastShotTime(std::chrono::high_resolution_clock::now()), _entityTemplate(_entityManager)
            {
                setRequirements<
                    engine::ecs::components::Transform,
                    rtype::ecs::components::PlayerShoot,
                    rtype::ecs::components::PlayerId>();
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
                    if (timeSinceLastShot.count() < 50)
                        return;

                    _lastShotTime = currentTime;
                    for (const auto &entity : getManagedEntities())
                    {
                        auto [transform, shoot, playerId] = _entityManager.getComponents<
                            engine::ecs::components::Transform,
                            rtype::ecs::components::PlayerShoot,
                            rtype::ecs::components::PlayerId>(entity);

                        if (inputEvent->playerId != playerId.id)
                            continue;

                        if (!shoot.isSpecialBulletBonusActivated) {
                            _entityTemplate.createPlayerBullet(transform.x, transform.y);
                        } else if (shoot.isSpecialBulletBonusActivated) {
                            _entityTemplate.createSpecialPlayerBullet(transform.x, transform.y);
                        }
                    }
                }
            }

        private:
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &_entityManager;
            std::chrono::time_point<std::chrono::high_resolution_clock> _lastShotTime;
            rtype::EntityTemplate _entityTemplate;
        };
    }
}