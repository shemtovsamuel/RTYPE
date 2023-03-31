#pragma once

#include "ecs/Event.hpp"

namespace rtype {
	namespace event {
		class DeathEvent : public engine::Event {
		public:
			int entity;
            bool isDead;
		};
	}
}
