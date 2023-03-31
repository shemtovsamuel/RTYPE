#pragma once

#include <engine/ecs/Event.hpp>

namespace rtype {
	namespace event {
		class MoveEvent : public engine::Event {
		public:
			int entity;
			float x, y;
		};
	}
}
