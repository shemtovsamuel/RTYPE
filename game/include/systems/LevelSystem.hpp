#pragma once

#include <engine/ecs/System.hpp>
#include <engine/ecs/Components.hpp>

#include "config/EcsConfig.hpp"
#include "Components.hpp"
#include "EntityTemplate.hpp"
#include "LevelManager.hpp"

namespace rtype
{
    namespace system
    {
        /**
         * @brief LevelSystem class which is used to have the operation of stages
         * 
         */
        class LevelSystem : public engine::ecs::System<rtype::config::ComponentCount, rtype::config::SystemCount>
        {
        public:
            /**
             * @brief Construct a new Level System object
             * 
             * @param entityManager 
             * @param levelManager 
             */
            LevelSystem(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& entityManager, rtype::LevelManager levelManager) : _entityManager(entityManager), _levelManager(levelManager)
            {
                setRequirements<rtype::ecs::components::EnnemiId>();
            }

            /**
             * @brief Update function to get levels
             * 
             * @param dt 
             */
            void update(const float dt)
            {
                if (getManagedEntities().size() == 0) {
                    _levelManager.setLevel(_levelManager.getLevel() + 1);
                    if (_levelManager.getLevel() % 5 == 0 && _levelManager.getLevel() != 0) {
                        _levelManager.createBossLevel(_levelManager.getLevel());
                    } else {
                        _levelManager.createLevel(_levelManager.getLevel());
                    }
                }
            }

        private:
            engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount>& _entityManager;
            rtype::LevelManager _levelManager;
        };
    }
}