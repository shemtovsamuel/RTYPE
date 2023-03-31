#pragma once

#include <engine/ecs/Event.hpp>

namespace rtype {
	namespace event {
        /*
         * @brief InputEvent class used when an input is triggered.
         * 
         */
		class InputEvent : public engine::Event {
		public:
			int key;
			int playerId;
		};
	}
}
