#include <engine/ecs/Components.hpp>

#include "EntityTemplate.hpp"
#include "Components.hpp"

rtype::EntityTemplate::EntityTemplate(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &entityManager, rtype::AssetManager &assetManager)
	: _entityManager(entityManager), _assetManager(assetManager)
{
}

int rtype::EntityTemplate::createPlayer(bool isOwner)
{
	float coordY = 1080.0f / (1 + 1);
	int playerNb = 0;
	if (playerNb < 1)
	{
		playerNb = 1;
	}
	if (playerNb > 5)
	{
		playerNb = playerNb % 5;
	}
	int playerSkin = 17 * playerNb;
	auto entity = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::State>(entity);
	_entityManager.addComponent<rtype::ecs::components::Health>(entity, 100, "Player");
	_entityManager.addComponent<engine::ecs::components::Transform>(entity, 20.0f, coordY);
	_entityManager.addComponent<engine::ecs::components::Velocity>(entity, 0.0f, 0.0f);

	sf::Texture &playerTexture = _assetManager.getTexture("r-typesheet42");
	sf::IntRect rect((33 * 3), 0, 33, playerSkin);
	sf::Vector2<float> scale(3.0f, 3.0f);
	_entityManager.addComponent<rtype::ecs::components::Sprite>(entity, playerTexture, rect, 10, scale);

	auto playerSprite = _entityManager.getComponent<rtype::ecs::components::Sprite>(entity);
	std::vector<sf::IntRect> frames;
	frames.push_back({(33 * 0), playerSkin, 33, 17});
	frames.push_back({(33 * 1), playerSkin, 33, 17});
	frames.push_back({(33 * 2), playerSkin, 33, 17});
	frames.push_back({(33 * 3), playerSkin, 33, 17});
	frames.push_back({(33 * 4), playerSkin, 33, 17});
	_entityManager.addComponent<rtype::ecs::components::SpriteAnimation>(entity, playerSprite.sprite, 0.5f, frames);

	_entityManager.addComponent<engine::ecs::components::Hitbox>(entity, 33.0f * scale.x, 17.0f * scale.y, "Player", "Player,PlayerBullet,Enemy");

	_entityManager.addComponent<rtype::ecs::components::MoveComponent>(entity);
	_entityManager.addComponent<rtype::ecs::components::PlayerShoot>(entity);

	_entityManager.addComponent<rtype::ecs::components::DebugTag>(entity, "Player");

	return entity;
}

int rtype::EntityTemplate::createBird()
{
	// size of the sprite : 522x126
	// size of the bird : 174x126

	float coordY = 0;
	auto bird = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::State>(bird);
	_entityManager.addComponent<rtype::ecs::components::Health>(bird, 100, "Player");
	_entityManager.addComponent<engine::ecs::components::Transform>(bird, 200.0f, coordY);
	_entityManager.addComponent<engine::ecs::components::Velocity>(bird, 0.0f, 0.0f);

	sf::Texture &playerTexture = _assetManager.getTexture("bird");
	sf::IntRect rect(0, 0, 174, 126);
	sf::Vector2<float> scale(0.5f, 0.5f);
	_entityManager.addComponent<rtype::ecs::components::Sprite>(bird, playerTexture, rect, 10, scale);

	auto playerSprite = _entityManager.getComponent<rtype::ecs::components::Sprite>(bird);
	std::vector<sf::IntRect> frames;
	frames.push_back({(174 * 0), 0, 174, 126});
	frames.push_back({(174 * 1), 0, 174, 126});
	frames.push_back({(174 * 2), 0, 174, 126});

	_entityManager.addComponent<rtype::ecs::components::SpriteAnimation>(bird, playerSprite.sprite, 0.5f, frames);
	_entityManager.addComponent<engine::ecs::components::Hitbox>(bird, 174.0f * scale.x, 126.0f * scale.y, "Player", "Player,PlayerBullet,Enemy");

	_entityManager.addComponent<rtype::ecs::components::MoveComponent>(bird);
	_entityManager.addComponent<rtype::ecs::components::PlayerShoot>(bird);

	_entityManager.addComponent<rtype::ecs::components::DebugTag>(bird, "Player");

	return bird;
}

int rtype::EntityTemplate::createObstacle1()
{
	auto obstacle1Top = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::Sprite>(obstacle1Top, _assetManager.getTexture("obstacle1Top"), 10);
	_entityManager.addComponent<engine::ecs::components::Velocity>(obstacle1Top, -300.0f, 0.0f);
	_entityManager.addComponent<engine::ecs::components::Transform>(obstacle1Top, 3000, 0);
	_entityManager.addComponent<engine::ecs::components::Hitbox>(obstacle1Top, 163.0f, 395.0f, "Obstacle1Top", "Bird", true);
	_entityManager.addComponent<rtype::ecs::components::Obstacle>(obstacle1Top);
	_entityManager.addComponent<rtype::ecs::components::Parallax>(obstacle1Top, 1920);

	auto obstacle1Bottom = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::Sprite>(obstacle1Bottom, _assetManager.getTexture("obstacle1Bottom"), 10);
	_entityManager.addComponent<engine::ecs::components::Velocity>(obstacle1Bottom, -300.0f, 0.0f);
	_entityManager.addComponent<engine::ecs::components::Transform>(obstacle1Bottom, 3000, 686);
	_entityManager.addComponent<engine::ecs::components::Hitbox>(obstacle1Bottom, 163.0f, 395.0f, "Obstacle1Bottom", "Bird", true);
	_entityManager.addComponent<rtype::ecs::components::Obstacle>(obstacle1Bottom);
	_entityManager.addComponent<rtype::ecs::components::Parallax>(obstacle1Bottom, 1920);

	return obstacle1Top + obstacle1Bottom;
}

int rtype::EntityTemplate::createObstacle2()
{
	auto obstacle2Top = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::Sprite>(obstacle2Top, _assetManager.getTexture("obstacle2Top"), 11);
	_entityManager.addComponent<engine::ecs::components::Velocity>(obstacle2Top, -300.0f, 0.0f);
	_entityManager.addComponent<engine::ecs::components::Transform>(obstacle2Top, 1920, 0);
	_entityManager.addComponent<engine::ecs::components::Hitbox>(obstacle2Top, 163.0f, 635.0f, "Obstacle2Top", "Bird", true);
	_entityManager.addComponent<rtype::ecs::components::Obstacle>(obstacle2Top);
	_entityManager.addComponent<rtype::ecs::components::Parallax>(obstacle2Top, 1920);

	auto obstacle2Bottom = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::Sprite>(obstacle2Bottom, _assetManager.getTexture("obstacle2Bottom"), 11);
	_entityManager.addComponent<engine::ecs::components::Velocity>(obstacle2Bottom, -300.0f, 0.0f);
	_entityManager.addComponent<engine::ecs::components::Transform>(obstacle2Bottom, 1920, 927);
	_entityManager.addComponent<engine::ecs::components::Hitbox>(obstacle2Bottom, 163.0f, 156.0f, "Obstacle2Bottom", "Bird", true);
	_entityManager.addComponent<rtype::ecs::components::Obstacle>(obstacle2Bottom);
	_entityManager.addComponent<rtype::ecs::components::Parallax>(obstacle2Bottom, 1920);

	return obstacle2Top + obstacle2Bottom;
}

int rtype::EntityTemplate::createObstacle3()
{
	auto obstacle3Top = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::Sprite>(obstacle3Top, _assetManager.getTexture("obstacle3Top"), 9);
	_entityManager.addComponent<engine::ecs::components::Velocity>(obstacle3Top, -300.0f, 0.0f);
	_entityManager.addComponent<engine::ecs::components::Transform>(obstacle3Top, 4000, 0);
	_entityManager.addComponent<engine::ecs::components::Hitbox>(obstacle3Top, 163.0f, 181.0f, "Obstacle3Top", "Bird", true);
	_entityManager.addComponent<rtype::ecs::components::Obstacle>(obstacle3Top);
	_entityManager.addComponent<rtype::ecs::components::Parallax>(obstacle3Top, 1920);

	auto obstacle3Bottom = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::Sprite>(obstacle3Bottom, _assetManager.getTexture("obstacle3Bottom"), 9);
	_entityManager.addComponent<engine::ecs::components::Velocity>(obstacle3Bottom, -300.0f, 0.0f);
	_entityManager.addComponent<engine::ecs::components::Transform>(obstacle3Bottom, 4000, 471);
	_entityManager.addComponent<engine::ecs::components::Hitbox>(obstacle3Bottom, 163.0f, 611.0f, "Obstacle3Bottom", "Bird", true);
	_entityManager.addComponent<rtype::ecs::components::Obstacle>(obstacle3Bottom);
	_entityManager.addComponent<rtype::ecs::components::Parallax>(obstacle3Bottom, 1920);

	return obstacle3Top + obstacle3Bottom;
}

int rtype::EntityTemplate::gameOver()
{
	auto gameOver = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::Sprite>(gameOver, _assetManager.getTexture("gameOver"), 22);
	_entityManager.addComponent<engine::ecs::components::Transform>(gameOver, 0, 0);

	return gameOver;
}

int rtype::EntityTemplate::createPlayerBullet(int x, int y)
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
	_entityManager.addComponent<rtype::ecs::components::Sprite>(entityBullet, bulletTexture, rect, 9, scale);

	// Animation
	auto bulletSprite = _entityManager.getComponent<rtype::ecs::components::Sprite>(entityBullet);
	std::vector<sf::IntRect> bulletFrames;
	bulletFrames.push_back({(50 * 0), 41, 50, 4});
	bulletFrames.push_back({(50 * 1), 41, 50, 4});
	bulletFrames.push_back({(50 * 2), 41, 50, 4});
	bulletFrames.push_back({(50 * 3), 41, 50, 4});
	bulletFrames.push_back({(50 * 4), 41, 50, 4});
	bulletFrames.push_back({(50 * 5), 41, 50, 4});
	bulletFrames.push_back({(50 * 6), 41, 50, 4});
	bulletFrames.push_back({(50 * 7), 41, 50, 4});
	_entityManager.addComponent<rtype::ecs::components::SpriteAnimation>(entityBullet, bulletSprite.sprite, 0.5f, bulletFrames);

	_entityManager.addComponent<rtype::ecs::components::DebugTag>(entityBullet, "PlayerBullet");

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
	_entityManager.addComponent<rtype::ecs::components::Sprite>(enemy, enemyTexture, rect, 10, scale);

	// Animation
	auto enemySprite = _entityManager.getComponent<rtype::ecs::components::Sprite>(enemy);
	std::vector<sf::IntRect> enemyFrames;
	enemyFrames.push_back({(161 * 0) + 22, 217, 161, 205});
	enemyFrames.push_back({(161 * 1) + 22, 217, 161, 205});
	enemyFrames.push_back({(161 * 2) + 22, 217, 161, 205});
	_entityManager.addComponent<rtype::ecs::components::SpriteAnimation>(enemy, enemySprite.sprite, 0.5f, enemyFrames);

	_entityManager.addComponent<engine::ecs::components::Hitbox>(enemy, 160.0f * scale.x, 205.0f * scale.y, "Enemy", "Player");
	_entityManager.addComponent<rtype::ecs::components::Health>(enemy, 100, "Enemy");

	_entityManager.addComponent<rtype::ecs::components::DebugTag>(enemy, "Enemy");

	return enemy;
}

int rtype::EntityTemplate::createParallax(float x, float y, const std::string &textureName, float speed, int spriteLayer)
{
	auto parallax = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::State>(parallax);
	_entityManager.addComponent<engine::ecs::components::Transform>(parallax, x, y);
	_entityManager.addComponent<engine::ecs::components::Velocity>(parallax, speed, 0.0f);
	_entityManager.addComponent<rtype::ecs::components::Parallax>(parallax, 3840);

	sf::Texture &parallaxTexture = _assetManager.getTexture(textureName);
	sf::IntRect rect(0, 0, 3840, 1080);
	sf::Vector2<float> scale(1.0f, 1.0f);
	_entityManager.addComponent<rtype::ecs::components::Sprite>(parallax, parallaxTexture, rect, spriteLayer, scale);

	_entityManager.addComponent<rtype::ecs::components::DebugTag>(parallax, std::string("Parallax ") + textureName);

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
	_entityManager.addComponent<rtype::ecs::components::Sprite>(bonus, bonusTexture, rect, 9, scale);

	// Animation
	auto bonusSprite = _entityManager.getComponent<rtype::ecs::components::Sprite>(bonus);
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
	_entityManager.addComponent<rtype::ecs::components::SpriteAnimation>(bonus, bonusSprite.sprite, 0.5f, bonusFrames);

	//_entityManager.addComponent<engine::ecs::components::Hitbox>(bonus, 33 * scale.x, 28 * scale.y, false, "Bonus");
	_entityManager.addComponent<rtype::ecs::components::Health>(bonus, 1, "Bonus");

	_entityManager.addComponent<rtype::ecs::components::DebugTag>(bonus, "Bonus");

	return bonus;
}