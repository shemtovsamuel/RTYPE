#pragma once

namespace rtype
{
	namespace config
	{
		/**
		 * @brief ECS configuration with max number of components, systems and entities. You can change it here if you need it.
		 * 
		 */
		static constexpr auto ComponentCount = 512;
		static constexpr auto SystemCount = 32;
		static constexpr auto EntitiesCount = 10000;
	}
}