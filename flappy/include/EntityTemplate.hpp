#pragma once

#include <engine/ecs/EntityManager.hpp>

#include "AssetManager.hpp"
#include "config/EcsConfig.hpp"

namespace rtype
{
	class EntityTemplate
	{
	public:
		EntityTemplate(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &entityManager, rtype::AssetManager &assetManager);

		int createPlayer(bool isOwner);
		int createBird();
		int createPlayerBullet(int x, int y);
		int createObstacle1();
		int createObstacle2();
		int createObstacle3();
		int gameOver();

		int createEnemy(float x, float y);
		int createBonus(float x, float y);
		int createParallax(float x, float y, const std::string &textureName, float speed, int spriteLayer);

	private:
		engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &_entityManager;
		rtype::AssetManager &_assetManager;
	};
}