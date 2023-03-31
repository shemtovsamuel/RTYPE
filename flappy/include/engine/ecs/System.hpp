#pragma once

#include <bitset>
#include <vector>

#include "Entity.hpp"
#include "Event.hpp"
#include "../graphical/GraphicalWindow.hpp"

namespace engine
{
	namespace ecs
	{

		template <std::size_t ComponentCount, std::size_t SystemCount>
		class EntityManager;

		/**
		 * @brief BaseSystem Interface used to store systems.
		 * 
		 * @tparam ComponentCount 
		 * @tparam SystemCount 
		 */
		template <std::size_t ComponentCount, std::size_t SystemCount>
		class System
		{
		public:
			virtual ~System() = default;

		protected:
			/**
			 * @brief Set the Requirements object
			 * 
			 * @tparam Ts 
			 */
			template <typename... Ts>
			void setRequirements()
			{
				(_requirements.set(Ts::type), ...);
			}

			/**
			 * @brief Get the Managed Entities object
			 * 
			 * @return const std::vector<Entity>& 
			 */
			const std::vector<Entity>& getManagedEntities() const
			{
				return _managedEntities;
			}

			/**
			 * @brief Add an entity to the system.
			 * 
			 * @param entity 
			 */
			virtual void onManagedEntityAdded([[maybe_unused]] Entity entity)
			{
			}

			/**
			 * @brief Remove an entity from the system.
			 * 
			 * @param entity 
			 */
			virtual void onManagedEntityRemoved([[maybe_unused]] Entity entity)
			{
			}

			/**
			 * @brief Update the system.
			 * 
			 * @param dt 
			 */
			virtual void update(const float dt) {}

			/**
			 * @brief Draw the system.
			 * 
			 * @param window 
			 */
			virtual void draw(engine::graphical::GraphicalWindow& window) {}

			/**
			 * @brief Handle an event.
			 * 
			 * @param event 
			 */
			virtual void handleEvent(const Event& event) {}

		private:
			friend EntityManager<ComponentCount, SystemCount>;

			std::bitset<ComponentCount> _requirements;
			std::size_t _type;
			std::vector<Entity> _managedEntities;
			std::vector<Index>* _entityToManagedEntity = nullptr;
			std::vector<std::unique_ptr<Event>> _events;

			/**
			 * @brief Set the Up object
			 * 
			 * @param type 
			 * @param entityToManagedEntity 
			 */
			void setUp(std::size_t type, std::vector<Index>* entityToManagedEntity)
			{
				_type = type;
				_entityToManagedEntity = entityToManagedEntity;
			}

			/**
			 * @brief On entity updated to the system.
			 * 
			 * @param entity 
			 * @param components 
			 */
			void onEntityUpdated(Entity entity, const std::bitset<ComponentCount>& components)
			{
				auto satisfied = (_requirements & components) == _requirements;
				auto managed = (*_entityToManagedEntity)[entity] != InvalidIndex;
				if (satisfied && !managed)
					addEntity(entity);
				else if (!satisfied && managed)
					removeEntity(entity);
				for (const auto& event : _events) {
					handleEvent(*event);
				}
				_events.clear();
			}

			/**
			 * @brief On entity removed to the system.
			 * 
			 * @param entity 
			 */
			void onEntityRemoved(Entity entity)
			{
				if ((*_entityToManagedEntity)[entity] != InvalidIndex)
					removeEntity(entity);
			}

			/**
			 * @brief Add an entity to the system.
			 * 
			 * @param entity 
			 */
			void addEntity(Entity entity)
			{
				(*_entityToManagedEntity)[entity] = static_cast<Index>(_managedEntities.size());
				_managedEntities.emplace_back(entity);
				onManagedEntityAdded(entity);
			}

			/**
			 * @brief Remove an entity from the system.
			 * 
			 * @param entity 
			 */
			void removeEntity(Entity entity)
			{
				onManagedEntityRemoved(entity);
				auto index = (*_entityToManagedEntity)[entity];
				(*_entityToManagedEntity)[_managedEntities.back()] = index;
				(*_entityToManagedEntity)[entity] = InvalidIndex;
				_managedEntities[index] = _managedEntities.back();
				_managedEntities.pop_back();
			}
		};

	}
}
