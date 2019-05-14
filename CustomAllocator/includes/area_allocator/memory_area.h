#pragma once

#include <cstddef>

namespace AreaAllocator
{
    struct memory_area
    {
        void* location;
        std::size_t size;
    };
}
