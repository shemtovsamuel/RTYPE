#pragma once

#include <engine/ecs/EntityManager.hpp>

#include "config/EcsConfig.hpp"

namespace rtype
{
	/**
	 * @brief EntityTemplate class which allows you to create entities
	 *
	 */
	class EntityTemplate
	{
	public:
		/**
		 * @brief Construct a new Entity Template object
		 *
		 * @param entityManager
		 * @param assetManager
		 */
		EntityTemplate(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &entityManager);

		/**
		 * @brief Create a Player object
		 *
		 * @param playerId for multiplayer
		 * @param isOwner
		 * @return int
		 */
		int createPlayer(int playerId, bool isOwner, std::pair<float, float> pos);

		/**
		 * @brief Create a Player Bullet object
		 *
		 * @param x position
		 * @param y position
		 * @return int
		 */
		int createPlayerBullet(int x, int y);

		/**
		 * @brief Create a Special Player Bullet object when a bonus is triggered
		 *
		 * @param x position
		 * @param y position
		 * @return int
		 */
		int createSpecialPlayerBullet(int x, int y);

		/**
		 * @brief Create a Enemy Bullet object
		 *
		 * @param x position
		 * @param y position
		 * @return int
		 */
		int createEnemyBullet(int x, int y);

				/**
		 * @brief Create a Boss Hive Bullet object
		 *
		 * @param x position
		 * @param y position
		 * @return int
		 */
		int createBossHiveBullet(int x, int y, float velX, float velY);

				/**
		 * @brief Create a Boss Alien Bullet object
		 *
		 * @param x position
		 * @param y position
		 * @param velX velocity in X
		 * @param velY velocity in Y
		 * @return int
		 */
		int createBossAlienBullet(int x, int y, float velX, float velY);

		/**
		 * @brief Create a Boss Alien object
		 *
		 * @param x position
		 * @param y position
		 * @return int
		 */
		int createBossAlien(float x, float y, int enemyId);

		/**
		 * @brief Create a Boss Hive object
		 *
		 * @param x position
		 * @param y position
		 * @return int
		 */
		int createBossHive(float x, float y, int enemyId);

		/**
		 * @brief Create a Enemy Crab object
		 *
		 * @param x position
		 * @param y position
		 * @return int
		 */
		int createEnemyCrab(float x, float y, int enemyId);

		/**
		 * @brief Create a Enemy Beetle object
		 *
		 * @param x position
		 * @param y position
		 * @return int
		 */
		int createEnemyBeetle(float x, float y, int enemyId);

		/**
		 * @brief Create a Bonus object
		 *
		 * @param x position
		 * @param y position
		 * @return int
		 */
		int createSpecialShootBonus(float x, float y, int id);

		/**
		 * @brief Create a Health Bonus object
		 *
		 * @param x
		 * @param y
		 * @return int
		 */
		int createHealthBonus(float x, float y, int id);

		/**
		 * @brief Create a Parallax object
		 *
		 * @param x position
		 * @param y position
		 * @param textureName for each assets
		 * @param speed the speed of each objects of the parallax
		 * @param spriteLayer the layer of the sprite
		 * @return int
		 */
		int createParallax(float x, float y, const std::string& textureName, float speed, int spriteLayer);

		/**
		 * @brief Create a top boundary object
		 *
		 * @param x position
		 * @param y position
		 * @return int
		 */
		int createTopBoundary(float x, float y);
		/**
		 * @brief Create a bottom boundary object
		 *
		 * @param x position
		 * @param y position
		 * @return int
		 */
		int createBottomBoundary(float x, float y);

		/**
		 * @brief Create a asteroid object
		 *
		 * @param x position
		 * @param y position
		 * @return int
		 */
		int createAsteroid(float x, float y, int id);

	private:
		engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &_entityManager;
	};
}