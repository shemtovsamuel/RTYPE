#pragma once

#include <vector>
#include <memory>
#include <string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include "Component.hpp"

namespace engine
{
	namespace ecs
	{
		namespace components
		{
			/**
			 * @brief ComponentType enum used to identify components. If you add a new component, add it here.
			 * 
			 */
			enum class ComponentType
			{
				Transform,
				Velocity,
				CubeSprite,
				SpriteComponent,
				SpriteAnimation,
				Hitbox,
				LastEngineComponent
			};

			/**
			 * @brief Transform component
			 * 
			 */
			struct Transform : public Component<Transform, ComponentType::Transform>
			{
				Transform(float X = 0.0, float Y = 0.0) : x(X), y(Y), prevX(X), prevY(Y)
				{
				}

				float x;
				float y;
				float prevX;
				float prevY;
			};

			/**
			 * @brief Velocity component
			 * 
			 */
			struct Velocity : public Component<Velocity, ComponentType::Velocity>
			{
				Velocity(float X = 0.0, float Y = 0.0) : x(X), y(Y)
				{
				}

				float x;
				float y;
			};

			/**
			 * @brief CubeSprite component
			 * 
			 */
			struct CubeSprite : public Component<CubeSprite, ComponentType::CubeSprite>
			{
				CubeSprite(sf::Color Color) : color(Color) {}
				CubeSprite(int red, int green, int blue, int alpha) {
					color = sf::Color(red, green, blue, alpha);
				}

				sf::Color color;
			};

			/**
			 * @brief SpriteComponent component
			 * 
			 */
			struct SpriteComponent : public Component<SpriteComponent, ComponentType::SpriteComponent>
			{
				SpriteComponent(const sf::Texture& texture, int spriteLayer = 0, sf::Vector2<float> scale = sf::Vector2<float>(1.0f, 1.0f))
				{
					sprite.setTexture(texture);
					sprite.setScale(scale);
					layer = spriteLayer;
				}
				SpriteComponent(const sf::Texture& texture, const sf::IntRect& rect, int spriteLayer = 0, sf::Vector2<float> scale = sf::Vector2<float>(1.0f, 1.0f))
				{
					sprite.setTexture(texture);
					sprite.setTextureRect(rect);
					sprite.setScale(scale);
					layer = spriteLayer;
				}

				sf::Sprite sprite;
				int layer;
			};

			/**
			 * @brief SpriteAnimation component
			 * 
			 */
			struct SpriteAnimation : public Component<SpriteAnimation, ComponentType::SpriteAnimation>
			{
				SpriteAnimation(sf::Sprite& sprite, float timePerFrame, std::vector<sf::IntRect> frames) : sprite(std::make_shared<sf::Sprite>(sprite)), timePerFrame(timePerFrame), frames(frames)
				{
				}

				std::vector<sf::IntRect> frames;
				std::shared_ptr<sf::Sprite> sprite;
				int currentFrame = 0;
				float timePerFrame;
				float accumulatedTime = 0;
			};

			/**
			 * @brief Hitbox component
			 * 
			 */
			struct Hitbox : public Component<Hitbox, ComponentType::Hitbox>
			{
				Hitbox(float Width, float Height, bool IsTrigger = false)
					: width(Width), height(Height), collided(false), isTrigger(IsTrigger), tag(""), triggerTags("")
				{
				}
				Hitbox(float Width, float Height, const std::string& Tag, const std::string& TriggerTags, bool IsTrigger = false)
					: width(Width), height(Height), collided(false), isTrigger(IsTrigger), tag(Tag), triggerTags(TriggerTags)
				{
				}

				float width;
				float height;
				bool collided;
				bool isTrigger;
				std::string tag;
				std::string triggerTags;
			};
		}
	}
}