#pragma once

#include <random>
#include <iostream>

#include <engine/ecs/System.hpp>
#include <engine/ecs/Components.hpp>

#include "config/EcsConfig.hpp"
#include "Components.hpp"

namespace rtype
{
    namespace system
    {
        /**
         * @brief ParticleSystem class to have the score the players
         * 
         */
        class ParticleSystem : public engine::ecs::System<rtype::config::ComponentCount, rtype::config::SystemCount>
        {
        public:
            /**
             * @brief Construct a new Particle System object
             * 
             * @param entityManager 
             */
            ParticleSystem(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& entityManager) : _entityManager(entityManager)
            {
                setRequirements<
                    rtype::ecs::components::ParticleSpawner,
                    engine::ecs::components::Transform
                >();
            }

            /**
             * @brief Update the particleSystem class
             * 
             * @param dt 
             */
            void update(const float dt)
            {
                for (const auto& entity : getManagedEntities())
                {
                    auto [particleSpawner, transform] = _entityManager.getComponents<
                        rtype::ecs::components::ParticleSpawner,
                        engine::ecs::components::Transform
                    >(entity);

                    if (particleSpawner.nbParticlesSpawned >= particleSpawner.nbParticles && particleSpawner.isLooping == false)
                        continue;
                    else if (particleSpawner.nbParticlesSpawned >= particleSpawner.nbParticles && particleSpawner.isLooping == true)
                        particleSpawner.nbParticlesSpawned = 0;

                    if (particleSpawner.timer > 0)
                        particleSpawner.timer -= dt;
                    else if (particleSpawner.timer <= 0) {
                        particleSpawner.timer = particleSpawner.timeBetweenSpawn;
                        particleSpawner.nbParticlesSpawned++;

                        int randomTransformX = generateRandomInt(particleSpawner.rangeSpawnX.x, particleSpawner.rangeSpawnX.y);
                        int randomTransformY = generateRandomInt(particleSpawner.rangeSpawnY.x, particleSpawner.rangeSpawnY.y);
                        int randomVelocityX = generateRandomInt(particleSpawner.rangeVelocityX.x, particleSpawner.rangeVelocityX.y);
                        int randomVelocityY = generateRandomInt(particleSpawner.rangeVelocityY.x, particleSpawner.rangeVelocityY.y);

                        auto particle = _entityManager.createEntity();
                        _entityManager.addComponent<rtype::ecs::components::LifeTime>(particle, particleSpawner.particleLifeTime);
                        _entityManager.addComponent<rtype::ecs::components::State>(particle);
                        _entityManager.addComponent<rtype::ecs::components::DebugTag>(particle, "Particle");
                        _entityManager.addComponent<rtype::ecs::components::Sprite>(particle, particleSpawner.sprite, particleSpawner.spriteLayout);

                        _entityManager.addComponent<engine::ecs::components::Transform>(particle, transform.x + randomTransformX, transform.y + randomTransformY);
                        _entityManager.addComponent<engine::ecs::components::Velocity>(particle, randomVelocityX, randomVelocityY);
                    }
                }
            }

        private:
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& _entityManager;

            int generateRandomInt(int min, int max)
            {
                std::random_device seed;
                std::mt19937 gen{seed()};
                std::uniform_int_distribution<> dist{min, max};
                return dist(gen);
            }
        };
    }
}