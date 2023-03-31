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
	 * @brief Score manager class to manage the score
	 * 
	 */
	class ScoreManager
	{
	public:
		/**
		 * @brief Construct a new Score Manager object
		 * 
		 * @param entityManager 
		 */
		ScoreManager(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &entityManager);
		
		/**
		 * @brief Display the score
		 * 
		 * @param window 
		 */
		void displayScore(sf::RenderWindow& window);

		/**
		 * @brief Update the score
		 * 
		 * @param score 
		 */
		void updateScore(int score);
		
		/**
		 * @brief Get the Score object
		 * 
		 * @return int 
		 */
		int getScore() const;
	private:
		engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &_entityManager;
		int _score;
	};
}