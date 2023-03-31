#pragma once

#include <cstddef>

namespace engine
{
    namespace ecs
    {
        /**
         * @brief Component class which is the base class for all components
         * 
         * @tparam T 
         * @tparam Type 
         */
        template <typename T, auto Type>
        class Component
        {
        public:
            static constexpr auto type = static_cast<std::size_t>(Type);
        };
    }
}