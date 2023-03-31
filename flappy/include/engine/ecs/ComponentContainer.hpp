#pragma once

#include <bitset>
#include <vector>

#include "Entity.hpp"

namespace engine
{
	namespace ecs
	{
		/**
		 * @brief BaseComponentContainer Interface used to store components.
		 * 
		 */
		class BaseComponentContainer
		{
		public:
			virtual ~BaseComponentContainer() = default;

			/**
			 * @brief Reserve the size of the container.
			 * 
			 * @param size 
			 */
			virtual void reserve(std::size_t size) = 0;

			/**
			 * @brief Try to remove an entity from the container.
			 * 
			 * @param entity 
			 * @return true 
			 * @return false 
			 */
			virtual bool tryRemove(Entity entity) = 0;
		};

		/**
		 * @brief ComponentContainer class used to store components.
		 * 
		 * @tparam T 
		 * @tparam ComponentCount 
		 * @tparam SystemCount 
		 */
		template <typename T, std::size_t ComponentCount, std::size_t SystemCount>
		class ComponentContainer : public BaseComponentContainer
		{
		public:
			ComponentContainer(std::vector<Index> &entityToComponent, std::vector<std::bitset<ComponentCount>> &entityToBitset) : _entityToComponent(entityToComponent), _entityToBitset(entityToBitset)
			{
			}

			/**
			 * @brief Reserve the size of the container.
			 * 
			 * @param size 
			 */
			virtual void reserve(std::size_t size) override
			{
				_components.reserve(size);
				_componentToEntity.reserve(size);
			}

			/**
			 * @brief Get a component of an entity.
			 * 
			 * @param entity 
			 * @return T& 
			 */
			T &get(Entity entity)
			{
				return _components[_entityToComponent[entity]];
			}

			/**
			 * @brief Get a component of an entity with const.
			 * 
			 * @param entity 
			 * @return const T& 
			 */
			const T &get(Entity entity) const
			{
				return _components[_entityToComponent[entity]];
			}

			/**
			 * @brief Add a component to an entity.
			 * 
			 * @tparam Args 
			 * @param entity 
			 * @param args 
			 */
			template <typename... Args>
			void add(Entity entity, Args &&...args)
			{
				auto index = static_cast<Index>(_components.size());

				_components.emplace_back(std::forward<Args>(args)...);
				_componentToEntity.emplace_back(entity);
				_entityToComponent[entity] = index;
				_entityToBitset[entity][T::type] = true;
			}

			/**
			 * @brief Remove a component from an entity.
			 * 
			 * @param entity 
			 */
			void remove(Entity entity)
			{
				_entityToBitset[entity][T::type] = false;

				auto index = _entityToComponent[entity];

				_components[index] = std::move(_components.back());
				_components.pop_back();
				_entityToComponent[_componentToEntity.back()] = index;
				_componentToEntity[index] = _componentToEntity.back();
				_componentToEntity.pop_back();
			}

			/**
			 * @brief Try to remove a component from an entity.
			 * 
			 * @param entity 
			 * @return true if the component was removed.
			 * @return false if the component was not removed.
			 */
			virtual bool tryRemove(Entity entity) override
			{
				if (_entityToBitset[entity][T::type])
				{
					remove(entity);
					return true;
				}
				return false;
			}

			/**
			 * @brief Get the Owner object of a component.
			 * 
			 * @param component 
			 * @return Entity 
			 */
			Entity getOwner(const T &component) const
			{
				auto begin = _components.data();
				auto index = static_cast<std::size_t>(&component - begin);

				return _componentToEntity[index];
			}

		private:
			std::vector<T> _components;
			std::vector<Entity> _componentToEntity;
			std::vector<Index> &_entityToComponent;
			std::vector<std::bitset<ComponentCount>> &_entityToBitset;
		};
	}
}