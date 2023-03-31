#pragma once

#include <engine/ecs/Component.hpp>
#include <engine/ecs/Components.hpp>

#include <SFML/Graphics.hpp>

namespace rtype
{
	namespace ecs
	{
		namespace components
		{
			enum class ComponentType
			{
				Sprite = (int)engine::ecs::components::ComponentType::LastEngineComponent,
				SpriteAnimation,
				MoveComponent,
				PlayerShoot,
				Health,
				State,
				Parallax,
				Obstacle,
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

			struct MoveComponent : public engine::ecs::Component<MoveComponent, ComponentType::MoveComponent>
			{
				MoveComponent()
				{
				}
			};

			struct PlayerShoot : public engine::ecs::Component<PlayerShoot, ComponentType::PlayerShoot>
			{
				PlayerShoot()
				{
				}
			};

			struct Health : public engine::ecs::Component<Health, ComponentType::Health>
			{
				Health(int Hp, const std::string &Tag) : hp(Hp), tag(Tag)
				{
				}

				int hp;
				std::string tag;
			};

			struct State : public engine::ecs::Component<State, ComponentType::State>
			{
				State() : toRemove(false)
				{
				}

				bool toRemove;
			};

			struct Parallax : public engine::ecs::Component<Parallax, ComponentType::Parallax>
			{
				Parallax(int Pos) : pos(Pos)
				{
				}
				int pos;
			};

			struct Obstacle : public engine::ecs::Component<Obstacle, ComponentType::Obstacle>
			{
				Obstacle()
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