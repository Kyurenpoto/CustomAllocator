#pragma once

#include <cstddef>

namespace
{
    struct allocator_already_initiated :
        public std::exception
    {};

    struct allocator_already_disposed :
        public std::exception
    {};
    
    struct allocator_runout :
        public std::exception
    {};
    
    struct allocator_empty :
        public std::exception
    {};
}

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

    void Initiate(const std::size_t sizeAreaMin,
                  const std::size_t sizeMemoryMax);
    void Dispose();
    void Allocate(memory_area & target);
    void Deallocate(memory_area & target);

	std::size_t getSizeAreaMin();
	std::size_t getSizeMemoryMax();
	std::size_t getSizeAllocated();
}
