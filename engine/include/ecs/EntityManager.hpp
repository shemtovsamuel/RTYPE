#pragma once

#include <memory>

#include "EntityContainer.hpp"
#include "ComponentContainer.hpp"
#include "System.hpp"
#include "../graphical/GraphicalWindow.hpp"

namespace engine
{
    namespace ecs
    {
        /**
         * @brief Entity manager class. It is used to create entities, add components to them and create systems with the entity linked.
         * 
         * @tparam ComponentCount 
         * @tparam SystemCount 
         */
        template <std::size_t ComponentCount, std::size_t SystemCount>
        class EntityManager
        {
        public:
            /**
             * @brief Construct a new Entity Manager object
             * 
             * @tparam T 
             */
            template <typename T>
            void registerComponent()
            {
                checkComponentType<T>();
                _componentContainers[T::type] = std::make_unique<ComponentContainer<T, ComponentCount, SystemCount>>(_entities.getEntityToComponent(T::type), _entities.getEntityToBitset());
            }

            /**
             * @brief Create a System object
             * 
             * @tparam T 
             * @tparam Args 
             * @param args 
             * @return T* 
             */
            template <typename T, typename... Args>
            T* createSystem(Args &&...args)
            {
                auto type = _systems.size();
                auto& system = _systems.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));

                system->setUp(type, &_entities.getEntityToManagedEntity(type));
                return static_cast<T*>(system.get());
            }

            /**
             * @brief Reserve the size of the containers.
             * 
             * @param size 
             */
            void reserve(std::size_t size)
            {
                for (auto i = std::size_t(0); i < ComponentCount; ++i)
                    if (_componentContainers[i])
                        _componentContainers[i]->reserve(size);
                _entities.reserve(size);
            }

            /**
             * @brief Create a Entity object
             * 
             * @return Entity 
             */
            Entity createEntity()
            {
                return _entities.create();
            }

            /**
             * @brief Remove a Entity object
             * 
             * @param entity 
             */
            void removeEntity(Entity entity)
            {
                for (auto i = std::size_t(0); i < ComponentCount; ++i)
                    if (_componentContainers[i])
                        _componentContainers[i]->tryRemove(entity);
                for (auto& system : _systems)
                    system->onEntityRemoved(entity);
                _entities.remove(entity);
            }

            /**
             * @brief Add a Component to a Entity
             * 
             * @tparam T 
             * @param entity 
             * @return true 
             * @return false 
             */
            template <typename T>
            bool hasComponent(Entity entity) const
            {
                checkComponentType<T>();
                return _entities.getBitset(entity)[T::type];
            }

            /**
             * @brief Check if a Entity has a set of Components
             * 
             * @tparam Ts 
             * @param entity 
             * @return true 
             * @return false 
             */
            template <typename... Ts>
            bool hasComponents(Entity entity) const
            {
                checkComponentTypes<Ts...>();

                auto requirements = std::bitset<ComponentCount>();

                (requirements.set(Ts::type), ...);
                return (requirements & _entities.getBitset(entity)) == requirements;
            }

            /**
             * @brief Get the Component object
             * 
             * @tparam T 
             * @param entity 
             * @return T& 
             */
            template <typename T>
            T& getComponent(Entity entity)
            {
                checkComponentType<T>();
                return getComponentContainer<T>()->get(entity);
            }

            /**
             * @brief Get the Component object with const
             * 
             * @tparam T 
             * @param entity 
             * @return const T& 
             */
            template <typename T>
            const T& getComponent(Entity entity) const
            {
                checkComponentType<T>();
                return getComponentContainer<T>()->get(entity);
            }

            /**
             * @brief Get the Components object
             * 
             * @tparam Ts 
             * @param entity 
             * @return std::tuple<Ts &...> 
             */
            template <typename... Ts>
            std::tuple<Ts &...> getComponents(Entity entity)
            {
                checkComponentTypes<Ts...>();
                return std::tie(getComponentContainer<Ts>()->get(entity)...);
            }

            /**
             * @brief Get the Components object
             * 
             * @tparam Ts 
             * @param entity 
             * @return std::tuple<const Ts &...> 
             */
            template <typename... Ts>
            std::tuple<const Ts &...> getComponents(Entity entity) const
            {
                checkComponentTypes<Ts...>();
                return std::tie(std::as_const(getComponentContainer<Ts>()->get(entity))...);
            }

            /**
             * @brief Add a Component to a Entity
             * 
             * @tparam T 
             * @tparam Args 
             * @param entity 
             * @param args 
             */
            template <typename T, typename... Args>
            void addComponent(Entity entity, Args &&...args)
            {
                checkComponentType<T>();
                getComponentContainer<T>()->add(entity, std::forward<Args>(args)...);
                const auto& bitset = _entities.getBitset(entity);
                for (auto& system : _systems)
                    system->onEntityUpdated(entity, bitset);
            }

            /**
             * @brief Remove a Component from a Entity
             * 
             * @tparam T 
             * @param entity 
             */
            template <typename T>
            void removeComponent(Entity entity)
            {
                checkComponentType<T>();
                getComponentContainer<T>()->remove(entity);
                const auto& bitset = _entities.getBitset(entity);
                for (auto& system : _systems)
                    system->onEntityUpdated(entity, bitset);
            }

            /**
             * @brief Get the Owner object
             * 
             * @tparam T 
             * @param component 
             * @return Entity 
             */
            template <typename T>
            Entity getOwner(const T& component) const
            {
                checkComponentType<T>();
                return getComponentContainer<T>()->getOwner(component);
            }

            /**
             * @brief Get the Component Container object
             * 
             * @param dt 
             */
            void updateSystems(const float dt) {
                for (auto& system : _systems) {
                    system->update(dt);
                }
            }

            /**
             * @brief Draw the Systems
             * 
             * @param window 
             */
            void drawSystems(engine::graphical::GraphicalWindow& window) {
                for (auto& system : _systems) {
                    system->draw(window);
                }
            }

            /**
             * @brief Dispatch an Event to all Systems
             * 
             * @param event 
             */
            void dispatchEvent(const Event& event) {
                for (auto& system : _systems) {
                    system->handleEvent(event);
                }
            }

        private:
            std::array<std::unique_ptr<BaseComponentContainer>, ComponentCount> _componentContainers;
            EntityContainer<ComponentCount, SystemCount> _entities;
            std::vector<std::unique_ptr<System<ComponentCount, SystemCount>>> _systems;

            /**
             * @brief Check if a Component is valid
             * 
             * @tparam T 
             */
            template <typename T>
            void checkComponentType() const
            {
                static_assert(T::type < ComponentCount);
            }

            /**
             * @brief Check if a set of Components are valid
             * 
             * @tparam Ts 
             */
            template <typename... Ts>
            void checkComponentTypes() const
            {
                (checkComponentType<Ts>(), ...);
            }

            /**
             * @brief Get the Component Container object
             * 
             * @tparam T 
             * @return auto 
             */
            template <typename T>
            auto getComponentContainer()
            {
                return static_cast<ComponentContainer<T, ComponentCount, SystemCount> *>(_componentContainers[T::type].get());
            }

            /**
             * @brief Get the Component Container object
             * 
             * @tparam T 
             * @return auto 
             */
            template <typename T>
            auto getComponentContainer() const
            {
                return static_cast<const ComponentContainer<T, ComponentCount, SystemCount> *>(_componentContainers[T::type].get());
            }
        };
    }
}
