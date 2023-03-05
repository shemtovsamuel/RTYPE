#pragma once

#include <engine/ecs/EntityManager.hpp>

#include "AssetManager.hpp"
#include "config/EcsConfig.hpp"

namespace rtype
{
	class EntityTemplate
	{
	public:
		EntityTemplate(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &entityManager, rtype::AssetManager& assetManager);

		int createPlayer(int playerId, bool isOwner);
		int createPlayerBullet(int playerId, int x, int y);

		int createEnemy(float x, float y);
		int createBonus(float x, float y);
		int createParallax(float x, float y, const std::string& textureName, float speed, int spriteLayer);
	private:
		engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &_entityManager;
		rtype::AssetManager& _assetManager;
	};
}