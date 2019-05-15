#pragma once

#include <cstddef>
#include <stdexcept>

#include "memory_area.h"
#include "area_info.h"

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

    void Initiate(const std::size_t sizeAreaMin,
                  const std::size_t sizeMemoryMax);
    void Dispose() noexcept;
    [[deprecated]]
    void Allocate(memory_area& target);
    void Allocate(std::size_t sizeArea);
    [[deprecated]]
    void Deallocate(memory_area& target);
    void Deallocate(area_info & target);

	std::size_t getSizeAreaMin();
	std::size_t getSizeMemoryMax();
	std::size_t getSizeAllocated();
}
