#pragma once

#include <limits>

namespace engine
{
    namespace ecs
    {
        /**
         * @brief Entity type used to identify entities.
         * 
         */
        using Entity = uint32_t;
        using Index = uint32_t;
        static constexpr auto InvalidIndex = std::numeric_limits<Index>::max();
    }
}