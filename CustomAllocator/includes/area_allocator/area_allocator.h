#pragma once

#include <cstddef>
#include <stdexcept>

namespace AreaAllocator
{
    struct allocator_already_initiated :
        public std::exception
    {};
    
    struct allocator_runout :
        public std::exception
    {};
    
    struct allocator_empty :
        public std::exception
    {};

#include "memory_area.h"

    enum class AreaResult
    {
        SUCCESSED,
        ALREADY_INITIATED,
        RUN_OUT,
        EMPTY,
        UNDEFINED
    };

    void Initiate(const std::size_t sizeAreaMin,
                  const std::size_t sizeMemoryMax);
    void Dispose() noexcept;
    void Allocate(memory_area & target);
    void Deallocate(memory_area & target);

	std::size_t getSizeAreaMin();
	std::size_t getSizeMemoryMax();
	std::size_t getSizeAllocated();
}
