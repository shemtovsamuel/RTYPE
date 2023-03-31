#pragma once

#include <engine/ecs/System.hpp>
#include <engine/ecs/Components.hpp>

#include "config/EcsConfig.hpp"
#include "Components.hpp"
#include "ScoreManager.hpp"

namespace rtype
{
    namespace system
    {
        /**
         * @brief ScoreSystem class to have the score the players
         * 
         */
        class ScoreSystem : public engine::ecs::System<rtype::config::ComponentCount, rtype::config::SystemCount>
        {
        public:
            /**
             * @brief Construct a new Score System object
             * 
             * @param entityManager 
             * @param scoreManager 
             */
            ScoreSystem(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& entityManager, rtype::ScoreManager scoreManager) : _entityManager(entityManager), _score(scoreManager)
            {
                setRequirements<
                    rtype::ecs::components::Health,
                    rtype::ecs::components::State,
                    rtype::ecs::components::Enemy
                >();
            }

            /**
             * @brief Update the scoreSystem class have the score
             * 
             * @param dt 
             */
            void update(const float dt)
            {
                for (const auto& entity : getManagedEntities())
                {
                    auto [health, state, enemy] = _entityManager.getComponents<
                        rtype::ecs::components::Health,
                        rtype::ecs::components::State,
                        rtype::ecs::components::Enemy
                    >(entity);

                    if (health.hp <= 0) {
                        _score.updateScore(5);
                    }
                }
            }

        private:
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& _entityManager;
            rtype::ScoreManager _score;
        };
    }
}