#pragma once

#include <engine/ecs/Component.hpp>
#include <engine/ecs/Components.hpp>

#include "../game/include/QueueManager.hpp"

namespace rtype
{
	namespace ecs
	{
		namespace components
		{
			/**
			 * @brief ComponentType enum which contains all the components types
			 *
			 */
			enum class ComponentType
			{
				Sprite = (int)engine::ecs::components::ComponentType::LastEngineComponent,
				SpriteAnimation,
				MoveComponent,
				PlayerShoot,
				PlayerId,
                EnnemiId,
                EnemyCrabId,
                EnemyBeetleId,
                ParralaxId,
                ShootBonusId,
                HealthBonusId,
                AsteroidId,
				Health,
				State,
				Parallax,
				Enemy,
				BossAlien,
				BossHive,
                DebugTag,
                LastComponent
			};

			/**
			 * @brief Sprite component
			 *
			 */
			struct Sprite : public engine::ecs::Component<Sprite, ComponentType::Sprite>
			{
				Sprite(const sf::Texture &texture, int spriteLayer = 0, sf::Vector2<float> scale = sf::Vector2<float>(1.0f, 1.0f))
				{
					sprite.setTexture(texture);
					sprite.setScale(scale);
					layer = spriteLayer;
				}
				Sprite(const sf::Texture &texture, const sf::IntRect &rect, int spriteLayer = 0, sf::Vector2<float> scale = sf::Vector2<float>(1.0f, 1.0f))
				{
					sprite.setTexture(texture);
					sprite.setTextureRect(rect);
					sprite.setScale(scale);
					layer = spriteLayer;
				}
				Sprite(const sf::Sprite& sprite, int spriteLayer = 0)
				{
					this->sprite = sprite;
					layer = spriteLayer;
				}

				sf::Sprite sprite;
				int layer;
			};

			/**
			 * @brief SpriteAnimation component
			 *
			 */
			struct SpriteAnimation : public engine::ecs::Component<SpriteAnimation, ComponentType::SpriteAnimation>
			{
				SpriteAnimation(sf::Sprite &sprite, float timePerFrame, std::vector<sf::IntRect> frames) : sprite(std::make_shared<sf::Sprite>(sprite)), timePerFrame(timePerFrame), frames(frames)
				{
				}

				std::vector<sf::IntRect> frames;
				std::shared_ptr<sf::Sprite> sprite;
				int currentFrame = 0;
				float timePerFrame;
				float accumulatedTime = 0;
			};

			/**
			 * @brief MoveComponent struct which contains the movement of the entity
			 *
			 */
			struct MoveComponent : public engine::ecs::Component<MoveComponent, ComponentType::MoveComponent>
			{
				MoveComponent()
				{
				}
			};

			/**
			 * @brief PlayerShoot struct which contains the player shoot
			 *
			 */
			struct PlayerShoot : public engine::ecs::Component<PlayerShoot, ComponentType::PlayerShoot>
			{
				PlayerShoot() : isSpecialBulletBonusActivated(false)
				{
				}

				bool isSpecialBulletBonusActivated;
			};

			/**
			 * @brief PlayerId struct which contains the player id
			 *
			 */
			struct PlayerId : public engine::ecs::Component<PlayerId, ComponentType::PlayerId>
			{
				PlayerId(int playerId, bool owner) : id(playerId), isOwner(owner)
				{
				}

				int id;
				bool isOwner;
			};

            struct EnnemiId : public engine::ecs::Component<EnnemiId, ComponentType::EnnemiId>
            {
                EnnemiId(int ennemiId) : id(ennemiId)
                {
                }

                int id;
            };

            struct EnemyCrabId : public engine::ecs::Component<EnemyCrabId, ComponentType::EnemyCrabId>
            {
                EnemyCrabId(int enemyCrab) : id(enemyCrab)
                {
                }

                int id;
            };

            struct EnemyBeetleId : public engine::ecs::Component<EnemyBeetleId, ComponentType::EnemyBeetleId>
            {
                EnemyBeetleId(int enemyBeetle) : id(enemyBeetle)
                {
                }

                int id;
            };

            struct ParralaxId : public engine::ecs::Component<ParralaxId, ComponentType::ParralaxId>
            {
                ParralaxId(int parralaxId) : id(parralaxId)
                {
                }

                int id;
            };

            struct ShootBonusId : public engine::ecs::Component<ShootBonusId, ComponentType::ShootBonusId>
            {
                ShootBonusId(int shootBonusId) : id(shootBonusId)
                {
                }

                int id;
            };

            struct HealthBonusId : public engine::ecs::Component<HealthBonusId, ComponentType::HealthBonusId>
            {
                HealthBonusId(int healthBonusId) : id(healthBonusId)
                {
                }

                int id;
            };

            struct AsteroidId : public engine::ecs::Component<AsteroidId, ComponentType::AsteroidId>
            {
                AsteroidId(int asteroidId) : id(asteroidId)
                {
                }

                int id;
            };

			/**
			 * @brief Health struct which contains the health of the entity
			 *
			 */
			struct Health : public engine::ecs::Component<Health, ComponentType::Health>
			{
				Health(int Hp, const std::string &Tag) : hp(Hp), tag(Tag)
				{
				}

				int hp;
				std::string tag;
			};

			/**
			 * @brief State struct which contains the state of the entity
			 *
			 */
			struct State : public engine::ecs::Component<State, ComponentType::State>
			{
				State() : toRemove(false)
				{
				}

				bool toRemove;
			};

			/**
			 * @brief Parallax struct which contains the parallax of the entity
			 *
			 */
			struct Parallax : public engine::ecs::Component<Parallax, ComponentType::Parallax>
			{
				Parallax()
				{
				}
			};

			/**
			 * @brief Enemy struct which contains the enemy of the entity
			 *
			 */
			struct Enemy : public engine::ecs::Component<Enemy, ComponentType::Enemy>
			{
				Enemy()
				{
				}
			};

			/**
			 * @brief BossAlien struct which contains the boss alien of the entity
			 *
			 */
			struct BossAlien : public engine::ecs::Component<BossAlien, ComponentType::BossAlien>
			{
				BossAlien()
				{
				}
			};

			/**
			 * @brief BossHive struct which contains the boss hive of the entity
			 *
			 */
			struct BossHive : public engine::ecs::Component<BossHive, ComponentType::BossHive>
			{
				BossHive()
				{
				}
			};

            struct DebugTag : public engine::ecs::Component<DebugTag, ComponentType::DebugTag>
            {
                DebugTag(const std::string &Tag) : tag(Tag)
                {
                }

                std::string tag;
            };
		}
	}
}