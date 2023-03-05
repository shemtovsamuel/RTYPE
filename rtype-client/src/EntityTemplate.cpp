#include <engine/ecs/Components.hpp>

#include "EntityTemplate.hpp"
#include "Components.hpp"

rtype::EntityTemplate::EntityTemplate(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &entityManager, rtype::AssetManager &assetManager)
	: _entityManager(entityManager), _assetManager(assetManager)
{
}

int rtype::EntityTemplate::createPlayer(int playerId, bool isOwner)
{
	float coordY = 1080.0f / (playerId + 1);
	int playerNb = playerId - 1;
	if (playerNb < 1) {
		playerNb = 1;
	}
	if (playerNb > 5) {
		playerNb = playerNb % 5;
	}
	int playerSkin = 17 * playerNb;
	auto entity = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::State>(entity);
	_entityManager.addComponent<rtype::ecs::components::PlayerId>(entity, playerId, isOwner);
	_entityManager.addComponent<rtype::ecs::components::Health>(entity, 100, "Player");
	_entityManager.addComponent<engine::ecs::components::Transform>(entity, 20.0f, coordY);
	_entityManager.addComponent<engine::ecs::components::Velocity>(entity, 0.0f, 0.0f);

	sf::Texture &playerTexture = _assetManager.getTexture("r-typesheet42");
	sf::IntRect rect((33 * 3), 0, 33, playerSkin);
	sf::Vector2<float> scale(3.0f, 3.0f);
	_entityManager.addComponent<engine::ecs::components::SpriteComponent>(entity, playerTexture, rect, 10, scale);

	auto playerSpriteComponent = _entityManager.getComponent<engine::ecs::components::SpriteComponent>(entity);
	std::vector<sf::IntRect> frames;
	frames.push_back({(33 * 0), playerSkin, 33, 17});
	frames.push_back({(33 * 1), playerSkin, 33, 17});
	frames.push_back({(33 * 2), playerSkin, 33, 17});
	frames.push_back({(33 * 3), playerSkin, 33, 17});
	frames.push_back({(33 * 4), playerSkin, 33, 17});
	_entityManager.addComponent<engine::ecs::components::SpriteAnimation>(entity, playerSpriteComponent.sprite, 0.5f, frames);

	_entityManager.addComponent<engine::ecs::components::Hitbox>(entity, 33.0f * scale.x, 17.0f * scale.y, "Player", "Player,PlayerBullet,Enemy");

	_entityManager.addComponent<rtype::ecs::components::MoveComponent>(entity);
	_entityManager.addComponent<rtype::ecs::components::PlayerShoot>(entity);

	return entity;
}

int rtype::EntityTemplate::createPlayerBullet(int playerId, int x, int y)
{
	auto entityBullet = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::State>(entityBullet);
	_entityManager.addComponent<engine::ecs::components::Transform>(entityBullet, x + 100.0f, y + 35.0f);
	_entityManager.addComponent<engine::ecs::components::Velocity>(entityBullet, 700.0f, 0.0f);
	_entityManager.addComponent<engine::ecs::components::Hitbox>(entityBullet, 50.0f, 4.0f, "PlayerBullet", "Player");

	auto &assetManager = rtype::AssetManager::getInstance();

	sf::Texture &bulletTexture = assetManager.getTexture("r-typesheet43");
	sf::IntRect rect(0, 41, 50, 4);
	sf::Vector2<float> scale(1.0f, 1.0f);
	_entityManager.addComponent<engine::ecs::components::SpriteComponent>(entityBullet, bulletTexture, rect, 9, scale);

	// Animation
	auto bulletSpriteComponent = _entityManager.getComponent<engine::ecs::components::SpriteComponent>(entityBullet);
	std::vector<sf::IntRect> bulletFrames;
	bulletFrames.push_back({(50 * 0), 41, 50, 4});
	bulletFrames.push_back({(50 * 1), 41, 50, 4});
	bulletFrames.push_back({(50 * 2), 41, 50, 4});
	bulletFrames.push_back({(50 * 3), 41, 50, 4});
	bulletFrames.push_back({(50 * 4), 41, 50, 4});
	bulletFrames.push_back({(50 * 5), 41, 50, 4});
	bulletFrames.push_back({(50 * 6), 41, 50, 4});
	bulletFrames.push_back({(50 * 7), 41, 50, 4});
	_entityManager.addComponent<engine::ecs::components::SpriteAnimation>(entityBullet, bulletSpriteComponent.sprite, 0.5f, bulletFrames);

	// Play sound
	assetManager.playSound("shoot");

	return entityBullet;
}

int rtype::EntityTemplate::createEnemy(float x, float y)
{
	auto enemy = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::State>(enemy);
	_entityManager.addComponent<engine::ecs::components::Transform>(enemy, x, y);
	_entityManager.addComponent<engine::ecs::components::Velocity>(enemy, -150.0f, 0.0f);

	sf::Texture &enemyTexture = _assetManager.getTexture("r-typesheet30");
	sf::IntRect rect(22, 217, 161, 205);
	sf::Vector2<float> scale(0.5f, 0.5f);
	_entityManager.addComponent<engine::ecs::components::SpriteComponent>(enemy, enemyTexture, rect, 10, scale);

	// Animation
	auto enemySpriteComponent = _entityManager.getComponent<engine::ecs::components::SpriteComponent>(enemy);
	std::vector<sf::IntRect> enemyFrames;
	enemyFrames.push_back({(161 * 0) + 22, 217, 161, 205});
	enemyFrames.push_back({(161 * 1) + 22, 217, 161, 205});
	enemyFrames.push_back({(161 * 2) + 22, 217, 161, 205});
	_entityManager.addComponent<engine::ecs::components::SpriteAnimation>(enemy, enemySpriteComponent.sprite, 0.5f, enemyFrames);

	_entityManager.addComponent<engine::ecs::components::Hitbox>(enemy, 160.0f * scale.x, 205.0f * scale.y, "Enemy", "Player");
	_entityManager.addComponent<rtype::ecs::components::Health>(enemy, 100, "Enemy");

	return enemy;
}

int rtype::EntityTemplate::createParallax(float x, float y, const std::string &textureName, float speed, int spriteLayer)
{
	auto parallax = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::State>(parallax);
	_entityManager.addComponent<engine::ecs::components::Transform>(parallax, x, y);
	_entityManager.addComponent<engine::ecs::components::Velocity>(parallax, speed, 0.0f);
	_entityManager.addComponent<rtype::ecs::components::Parallax>(parallax);

	sf::Texture &parallaxTexture = _assetManager.getTexture(textureName);
	sf::IntRect rect(0, 0, 3840, 1080);
	sf::Vector2<float> scale(1.0f, 1.0f);
	_entityManager.addComponent<engine::ecs::components::SpriteComponent>(parallax, parallaxTexture, rect, spriteLayer, scale);

	return parallax;
}

int rtype::EntityTemplate::createBonus(float x, float y)
{
	auto bonus = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::State>(bonus);
	_entityManager.addComponent<engine::ecs::components::Transform>(bonus, x, y);
	_entityManager.addComponent<engine::ecs::components::Velocity>(bonus, -250.0f, 0.0f);

	sf::Texture &bonusTexture = _assetManager.getTexture("r-typesheet13");
	sf::IntRect rect(33, 70, 28, 33);
	sf::Vector2<float> scale(1.0f, 1.0f);
	_entityManager.addComponent<engine::ecs::components::SpriteComponent>(bonus, bonusTexture, rect, 9, scale);

	// Animation
	auto bonusSpriteComponent = _entityManager.getComponent<engine::ecs::components::SpriteComponent>(bonus);
	std::vector<sf::IntRect> bonusFrames;
	bonusFrames.push_back({(33 * 0), 70, 28, 33});
	bonusFrames.push_back({(33 * 1), 70, 28, 33});
	bonusFrames.push_back({(33 * 2), 70, 28, 33});
	bonusFrames.push_back({(33 * 3), 70, 28, 33});
	bonusFrames.push_back({(33 * 4), 70, 28, 33});
	bonusFrames.push_back({(33 * 5), 70, 28, 33});
	bonusFrames.push_back({(33 * 6), 70, 28, 33});
	bonusFrames.push_back({(33 * 7), 70, 28, 33});
	bonusFrames.push_back({(33 * 0), 103, 28, 33});
	bonusFrames.push_back({(33 * 1), 103, 28, 33});
	bonusFrames.push_back({(33 * 2), 103, 28, 33});
	bonusFrames.push_back({(33 * 3), 103, 28, 33});
	bonusFrames.push_back({(33 * 4), 103, 28, 33});
	bonusFrames.push_back({(33 * 5), 103, 28, 33});
	bonusFrames.push_back({(33 * 6), 103, 28, 33});
	bonusFrames.push_back({(33 * 7), 103, 28, 33});
	_entityManager.addComponent<engine::ecs::components::SpriteAnimation>(bonus, bonusSpriteComponent.sprite, 0.5f, bonusFrames);

	//_entityManager.addComponent<engine::ecs::components::Hitbox>(bonus, 33 * scale.x, 28 * scale.y, false, "Bonus");
	_entityManager.addComponent<rtype::ecs::components::Health>(bonus, 1, "Bonus");

	return bonus;
}