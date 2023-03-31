#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <set>

#include <SFML/Graphics.hpp>

#include <engine/ecs/Component.hpp>
#include <engine/ecs/Components.hpp>
#include <engine/ecs/EntityManager.hpp>

#include "config/EcsConfig.hpp"

#include "events/InputEvent.hpp"
#include "EntityTemplate.hpp"

namespace rtype
{
	/**
	 * @brief Level manager class to manage the creation of levels
	 * 
	 */
	class LevelManager
	{
	public:
		/**
		 * @brief Construct a new Level Manager object
		 * 
		 * @param entityManager 
		 */
		LevelManager(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &entityManager);
		
		/**
		 * @brief Create a Level object
		 * 
		 * @param level 
		 */
		void createLevel(int level);

		/**
		 * @brief Create a Boss Level object
		 * 
		 * @param level 
		 */
		void createBossLevel(int level);

		/**
		 * @brief Get the Level object
		 * 
		 * @return int 
		 */
		int getLevel() const;
		void setLevel(int level);

	private:
		engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &_entityManager;
        rtype::EntityTemplate _entityTemplate;
		int _level;
        int _enemiId;
        int _asteroidId;
		float _coordX;
		float _coordY;
		float _offset;
	};
}