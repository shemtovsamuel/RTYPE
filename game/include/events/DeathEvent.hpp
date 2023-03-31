#pragma once

#include <engine/ecs/Event.hpp>

namespace rtype {
	namespace event {
        /*
         * @brief DeathEvent class when the death of an entity is triggered
         * 
         */
		class DeathEvent : public engine::Event {
		public:
			int entity;
            bool isDead;
		};
	}
}
