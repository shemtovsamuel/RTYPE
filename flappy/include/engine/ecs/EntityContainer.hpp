#pragma once

#include <array>
#include <bitset>
#include <vector>
#include <numeric>

#include "Entity.hpp"

namespace engine
{
    namespace ecs
    {
        /**
         * @brief EntityContainer class used to store entities.
         * 
         * @tparam ComponentCount 
         * @tparam SystemCount 
         */
        template <std::size_t ComponentCount, std::size_t SystemCount>
        class EntityContainer
        {
        public:
            /**
             * @brief Construct a new EntityContainer object.
             * 
             * @param size 
             */
            void reserve(std::size_t size)
            {
                _freeEntities.resize(size);
                std::iota(std::begin(_freeEntities), std::end(_freeEntities), 0);
                _entityToBitset.resize(size);
                for (auto& entityToComponent : _entityToComponents)
                    entityToComponent.resize(size);
                for (auto& entityToManagedEntity : _entityToManagedEntities)
                    entityToManagedEntity.resize(size);
            }

            /**
             * @brief Get the Entity To Bitset object
             * 
             * @return std::vector<std::bitset<ComponentCount>>& 
             */
            std::vector<std::bitset<ComponentCount>>& getEntityToBitset()
            {
                return _entityToBitset;
            }

            /**
             * @brief Get the Entity To Bitset object
             * 
             * @param entity 
             * @return const std::bitset<ComponentCount>& 
             */
            const std::bitset<ComponentCount>& getBitset(Entity entity) const
            {
                return _entityToBitset[entity];
            }

            /**
             * @brief Get the Entity To Component object
             * 
             * @param type 
             * @return std::vector<Index>& 
             */
            std::vector<Index>& getEntityToComponent(std::size_t type)
            {
                return _entityToComponents[type];
            }

            /**
             * @brief Get the Entity To Managed Entity object
             * 
             * @param type 
             * @return std::vector<Index>& 
             */
            std::vector<Index>& getEntityToManagedEntity(std::size_t type)
            {
                return _entityToManagedEntities[type];
            }

            /**
             * @brief Create a new Entity object.
             * 
             * @return Entity 
             */
            Entity create()
            {
                auto entity = Entity();
                if (_freeEntities.empty())
                {
                    entity = static_cast<Entity>(_entityToBitset.size());
                    _entityToBitset.emplace_back();
                    for (auto& entityToComponent : _entityToComponents)
                        entityToComponent.emplace_back();
                    for (auto& entityToManagedEntity : _entityToManagedEntities)
                        entityToManagedEntity.emplace_back(InvalidIndex);
                }
                else
                {
                    entity = _freeEntities.back();
                    _freeEntities.pop_back();
                    _entityToBitset[entity].reset();
                    for (auto& entityToManagedEntity : _entityToManagedEntities)
                        entityToManagedEntity[entity] = InvalidIndex;
                }
                return entity;
            }

            /**
             * @brief Remove an Entity object.
             * 
             * @param entity 
             */
            void remove(Entity entity)
            {
                _freeEntities.push_back(entity);
            }

        private:
            std::vector<std::bitset<ComponentCount>> _entityToBitset;
            std::array<std::vector<Index>, ComponentCount> _entityToComponents;
            std::array<std::vector<Index>, SystemCount> _entityToManagedEntities;
            std::vector<Entity> _freeEntities;
        };
    }
}
