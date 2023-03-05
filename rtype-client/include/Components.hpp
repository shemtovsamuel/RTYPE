#pragma once

#include <engine/ecs/Component.hpp>
#include <engine/ecs/Components.hpp>

namespace rtype
{
	namespace ecs
	{
		namespace components
		{
			enum class ComponentType
			{
				MoveComponent = (int)engine::ecs::components::ComponentType::LastEngineComponent,
				PlayerShoot,
				PlayerId,
				Health,
				State,
				Parallax
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

			struct PlayerId : public engine::ecs::Component<PlayerId, ComponentType::PlayerId>
			{
				PlayerId(int playerId, bool owner) : id(playerId), isOwner(owner)
				{
				}

				int id;
				bool isOwner;
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
				Parallax()
				{
				}
			};
		}
	}
}