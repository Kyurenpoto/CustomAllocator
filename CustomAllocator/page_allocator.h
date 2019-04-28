#pragma once

namespace AreaAllocator
{
    struct memory_area
    {
        void* location;
        std::size_t size;
    };

    enum class AreaResult
    {
        SUCCESSED,
        ALREADY_INITIATED,
        ALREADY_DISPOSED,
        RUN_OUT,
        EMPTY,
        UNDEFINED
    };

    AreaResult Initiate(const std::size_t sizeAreaMin,
                        const std::size_t sizeMemoryMax);
    AreaResult Dispose();
    AreaResult Allocate(memory_area & target);
    AreaResult Deallocate(memory_area & target);
}
