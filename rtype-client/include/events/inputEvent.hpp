#pragma once

#include <engine/ecs/Event.hpp>

namespace rtype {
	namespace event {
		class InputEvent : public engine::Event {
		public:
			int key;
			int playerId;
		};
	}
}
