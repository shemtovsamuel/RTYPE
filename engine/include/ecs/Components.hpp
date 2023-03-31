#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Component.hpp"
#include "../graphical/GraphicalVector.hpp"

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