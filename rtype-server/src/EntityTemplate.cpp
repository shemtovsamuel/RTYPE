#include <engine/ecs/Components.hpp>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "EntityTemplate.hpp"
#include "Components.hpp"

rtype::EntityTemplate::EntityTemplate(engine::ecs::EntityManager<rtype::config::ComponentCount, rtype::config::SystemCount> &entityManager)
	: _entityManager(entityManager)
{
}

int rtype::EntityTemplate::createPlayer(int playerId, bool isOwner, std::pair<float, float> pos)
{
	int playerNb = playerId - 1;
	if (playerNb < 1) {
		playerNb = 1;
	}
	if (playerNb > 5) {
		playerNb = playerNb % 5;
	}
	int playerSkin = 17 * 0;
	auto entity = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::State>(entity);
	_entityManager.addComponent<rtype::ecs::components::PlayerId>(entity, playerId, isOwner);
	_entityManager.addComponent<rtype::ecs::components::Health>(entity, 100, "Player");
	_entityManager.addComponent<engine::ecs::components::Transform>(entity, pos.first, pos.second);
	_entityManager.addComponent<engine::ecs::components::Velocity>(entity, 0.0f, 0.0f);

	sf::IntRect rect((33 * 3), 0, 33, playerSkin);
	sf::Vector2<float> scale(3.0f, 3.0f);

	_entityManager.addComponent<engine::ecs::components::Hitbox>(entity, 33.0f * scale.x, 17.0f * scale.y, "Player", "Player,PlayerBullet,Enemy");

	_entityManager.addComponent<rtype::ecs::components::MoveComponent>(entity);
	_entityManager.addComponent<rtype::ecs::components::PlayerShoot>(entity);

	_entityManager.addComponent<rtype::ecs::components::DebugTag>(entity, "Player");

	return entity;
}

int rtype::EntityTemplate::createPlayerBullet(int x, int y)
{
	auto entityBullet = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::State>(entityBullet);
	_entityManager.addComponent<engine::ecs::components::Transform>(entityBullet, x + 100.0f, y + 35.0f);
	_entityManager.addComponent<engine::ecs::components::Velocity>(entityBullet, 700.0f, 0.0f);
	_entityManager.addComponent<engine::ecs::components::Hitbox>(entityBullet, 50.0f, 4.0f, "PlayerBullet", "", true);

	return entityBullet;
}

int rtype::EntityTemplate::createEnemyBullet(int x, int y)
{
	auto entityBullet = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::State>(entityBullet);
	_entityManager.addComponent<engine::ecs::components::Transform>(entityBullet, x - 50.0f, y + 40.0f);
	_entityManager.addComponent<engine::ecs::components::Velocity>(entityBullet, -500.0f, 0.0f);
	_entityManager.addComponent<engine::ecs::components::Hitbox>(entityBullet, 50.0f, 4.0f, "EnemyBullet", "", true);

	_entityManager.addComponent<rtype::ecs::components::DebugTag>(entityBullet, "PlayerBullet");

	return entityBullet;
}

int rtype::EntityTemplate::createBossHiveBullet(int x, int y, float velX, float velY)
{
	auto entityBullet = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::State>(entityBullet);
	_entityManager.addComponent<engine::ecs::components::Transform>(entityBullet, x - 50.0f, y + 40.0f);
	_entityManager.addComponent<engine::ecs::components::Velocity>(entityBullet, velX * 600, velY * 600);
	_entityManager.addComponent<engine::ecs::components::Hitbox>(entityBullet, 31.0f, 29.0f, "BossHiveBullet", "", true);

	_entityManager.addComponent<rtype::ecs::components::DebugTag>(entityBullet, "BossHiveBullet");

	return entityBullet;
}

int rtype::EntityTemplate::createBossAlienBullet(int x, int y, float velX, float velY)
{
	auto entityBullet = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::State>(entityBullet);
	_entityManager.addComponent<engine::ecs::components::Transform>(entityBullet, x - 50.0f, y + 40.0f);
	_entityManager.addComponent<engine::ecs::components::Velocity>(entityBullet, velX * 400, velY * 400);
	_entityManager.addComponent<engine::ecs::components::Hitbox>(entityBullet, 31.0f, 29.0f, "BossAlienBullet", "", true);

	_entityManager.addComponent<rtype::ecs::components::DebugTag>(entityBullet, "BossAlienBullet");

	return entityBullet;
}

int rtype::EntityTemplate::createSpecialPlayerBullet(int x, int y)
{
	auto entityBullet = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::State>(entityBullet);
	_entityManager.addComponent<engine::ecs::components::Transform>(entityBullet, x + 100.0f, y + 35.0f);
	_entityManager.addComponent<engine::ecs::components::Velocity>(entityBullet, 950.0f, 0.0f);

    sf::Vector2<float> scale(3.5f, 3.5f);

	_entityManager.addComponent<engine::ecs::components::Hitbox>(entityBullet, 81.0f * scale.x, 16.0f * scale.y, "PlayerBullet", "", true);

	return entityBullet;
}

// Boss Hive
int rtype::EntityTemplate::createBossHive(float x, float y, int enemyId)
{
	auto enemy = _entityManager.createEntity();
    _entityManager.addComponent<rtype::ecs::components::EnnemiId>(enemy, enemyId);
	_entityManager.addComponent<rtype::ecs::components::State>(enemy);
	_entityManager.addComponent<engine::ecs::components::Transform>(enemy, x, y);
	_entityManager.addComponent<engine::ecs::components::Velocity>(enemy, 0.0f, 0.0f);

	sf::Vector2<float> scale(3.5f, 3.5f);

	_entityManager.addComponent<engine::ecs::components::Hitbox>(enemy, 264.0f * scale.x, 143.0f * scale.y, "BossHive", "Player");
	_entityManager.addComponent<rtype::ecs::components::Health>(enemy, 500, "BossHive");
	_entityManager.addComponent<rtype::ecs::components::BossHive>(enemy);

	_entityManager.addComponent<rtype::ecs::components::DebugTag>(enemy, "BossHive");

	return enemy;
}

// Boss Alien
int rtype::EntityTemplate::createBossAlien(float x, float y, int enemyId)
{
	auto enemy = _entityManager.createEntity();
    _entityManager.addComponent<rtype::ecs::components::EnnemiId>(enemy, enemyId);
	_entityManager.addComponent<rtype::ecs::components::State>(enemy);
	_entityManager.addComponent<engine::ecs::components::Transform>(enemy, x, y);
	_entityManager.addComponent<engine::ecs::components::Velocity>(enemy, 0.0f, 0.0f);

	sf::Vector2<float> scale(3.5f, 3.5f);

	_entityManager.addComponent<engine::ecs::components::Hitbox>(enemy, 160.0f * scale.x, 205.0f * scale.y, "BossAlien", "Player");
	_entityManager.addComponent<rtype::ecs::components::Health>(enemy, 500, "BossAlien");
	_entityManager.addComponent<rtype::ecs::components::BossAlien>(enemy);

	_entityManager.addComponent<rtype::ecs::components::DebugTag>(enemy, "BossAlien");

	return enemy;
}

// Enemy Crab
int rtype::EntityTemplate::createEnemyCrab(float x, float y, int enemyId)
{
	auto enemy = _entityManager.createEntity();
    _entityManager.addComponent<rtype::ecs::components::EnnemiId>(enemy, enemyId);
    _entityManager.addComponent<rtype::ecs::components::EnemyCrabId>(enemy, enemyId);
	_entityManager.addComponent<rtype::ecs::components::State>(enemy);
	_entityManager.addComponent<engine::ecs::components::Transform>(enemy, x, y);
	_entityManager.addComponent<engine::ecs::components::Velocity>(enemy, 0.0f, 0.0f);

	sf::IntRect rect(135, 36, 29, 28);
	sf::Vector2<float> scale(3.0f, 3.0f);

	_entityManager.addComponent<engine::ecs::components::Hitbox>(enemy, 29.0f * scale.x, 28.0f * scale.y, "Enemy", "Player");
	_entityManager.addComponent<rtype::ecs::components::Health>(enemy, 10, "Enemy");
	_entityManager.addComponent<rtype::ecs::components::Enemy>(enemy);

    _entityManager.addComponent<rtype::ecs::components::DebugTag>(enemy, "Enemy");

	return enemy;
}

// Enemy Beetle
int rtype::EntityTemplate::createEnemyBeetle(float x, float y, int enemyId)
{
	auto enemy = _entityManager.createEntity();
    _entityManager.addComponent<rtype::ecs::components::EnnemiId>(enemy, enemyId);
    _entityManager.addComponent<rtype::ecs::components::EnemyBeetleId>(enemy, enemyId);
	_entityManager.addComponent<rtype::ecs::components::State>(enemy);
	_entityManager.addComponent<engine::ecs::components::Transform>(enemy, x, y);
	_entityManager.addComponent<engine::ecs::components::Velocity>(enemy, 0.0f, 0.0f);

	sf::Vector2<float> scale(3.0f, 3.0f);

	_entityManager.addComponent<engine::ecs::components::Hitbox>(enemy, 32.0f * scale.x, 28.0f * scale.y, "Enemy", "Player");
	_entityManager.addComponent<rtype::ecs::components::Health>(enemy, 10, "Enemy");
	_entityManager.addComponent<rtype::ecs::components::Enemy>(enemy);

    _entityManager.addComponent<rtype::ecs::components::DebugTag>(enemy, "Enemy");

	return enemy;
}

int rtype::EntityTemplate::createParallax(float x, float y, const std::string &textureName, float speed, int spriteLayer)
{
	auto parallax = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::ParralaxId>(parallax, spriteLayer);
    _entityManager.addComponent<rtype::ecs::components::State>(parallax);
	_entityManager.addComponent<engine::ecs::components::Transform>(parallax, x, y);
	_entityManager.addComponent<engine::ecs::components::Velocity>(parallax, speed, 0.0f);
	_entityManager.addComponent<rtype::ecs::components::Parallax>(parallax);

	_entityManager.addComponent<rtype::ecs::components::DebugTag>(parallax, std::string("Parallax ") + textureName);

	return parallax;
}

int rtype::EntityTemplate::createSpecialShootBonus(float x, float y, int id)
{
	auto bonus = _entityManager.createEntity();
    _entityManager.addComponent<rtype::ecs::components::ShootBonusId>(bonus, id);
	_entityManager.addComponent<rtype::ecs::components::State>(bonus);
	_entityManager.addComponent<engine::ecs::components::Transform>(bonus, x, y);
	_entityManager.addComponent<engine::ecs::components::Velocity>(bonus, -250.0f, 0.0f);

	sf::Vector2<float> scale(1.0f, 1.0f);

	_entityManager.addComponent<engine::ecs::components::Hitbox>(bonus, 33 * scale.x, 28 * scale.y, "Bonus", "", true);
	_entityManager.addComponent<rtype::ecs::components::Health>(bonus, 1, "Bonus");

	_entityManager.addComponent<rtype::ecs::components::DebugTag>(bonus, "Bonus");

	return bonus;
}

int rtype::EntityTemplate::createHealthBonus(float x, float y, int id)
{
	auto bonus = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::HealthBonusId>(bonus, id);
	_entityManager.addComponent<rtype::ecs::components::State>(bonus);
	_entityManager.addComponent<engine::ecs::components::Transform>(bonus, x, y);
	_entityManager.addComponent<engine::ecs::components::Velocity>(bonus, -250.0f, 0.0f);

	sf::Vector2<float> scale(1.0f, 1.0f);

	_entityManager.addComponent<engine::ecs::components::Hitbox>(bonus, 33 * scale.x, 28 * scale.y, "HealthBonus", "", true);
	_entityManager.addComponent<rtype::ecs::components::Health>(bonus, 1, "HealthBonus");

	_entityManager.addComponent<rtype::ecs::components::DebugTag>(bonus, "HealthBonus");

	return bonus;
}

int rtype::EntityTemplate::createTopBoundary(float x, float y)
{
	auto top_border = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::State>(top_border);
	_entityManager.addComponent<engine::ecs::components::Transform>(top_border, x, y);
	_entityManager.addComponent<engine::ecs::components::Velocity>(top_border, 0.0f, 0.0f);

	sf::Vector2<float> scale(5.0f, 1.0f);

	_entityManager.addComponent<engine::ecs::components::Hitbox>(top_border, 594 * scale.x, 50 * scale.y, "Boundary", "Player");

	_entityManager.addComponent<rtype::ecs::components::DebugTag>(top_border, "TopBoundary");

	return top_border;
}

int rtype::EntityTemplate::createBottomBoundary(float x, float y)
{
	auto bottom_border = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::State>(bottom_border);
	_entityManager.addComponent<engine::ecs::components::Transform>(bottom_border, x, y);
	_entityManager.addComponent<engine::ecs::components::Velocity>(bottom_border, 0.0f, 0.0f);

	sf::Vector2<float> scale(5.0f, 1.0f);

	_entityManager.addComponent<engine::ecs::components::Hitbox>(bottom_border, 594 * scale.x, 50 * scale.y, "Boundary", "Player");

	_entityManager.addComponent<rtype::ecs::components::DebugTag>(bottom_border, "BottomBoundary");

	return bottom_border;
}

int rtype::EntityTemplate::createAsteroid(float x, float y, int id)
{
	auto asteroid = _entityManager.createEntity();
	_entityManager.addComponent<rtype::ecs::components::AsteroidId>(asteroid, id);
	_entityManager.addComponent<rtype::ecs::components::State>(asteroid);
	_entityManager.addComponent<engine::ecs::components::Transform>(asteroid, x, y);
	_entityManager.addComponent<engine::ecs::components::Velocity>(asteroid, -200.0f, 0.0f);

	sf::Vector2<float> scale(2.0f, 2.0f);

	_entityManager.addComponent<engine::ecs::components::Hitbox>(asteroid, 33 * scale.x, 28 * scale.y, "Asteroid", "", true);
	_entityManager.addComponent<rtype::ecs::components::Health>(asteroid, 1, "Asteroid");

	_entityManager.addComponent<rtype::ecs::components::DebugTag>(asteroid, "Asteroid");

	return asteroid;
}
