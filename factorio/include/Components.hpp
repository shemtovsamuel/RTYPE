#pragma once

#include <engine/ecs/Component.hpp>
#include <engine/ecs/Components.hpp>

#include <SFML/Graphics.hpp>

namespace factorio
{
	namespace ecs
	{
		namespace components
		{
			enum class ComponentType
			{
				Sprite = (int)engine::ecs::components::ComponentType::LastEngineComponent,
				SpriteAnimation,
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
		}
	}
}