#pragma once

#include <cstddef>
#include <stdexcept>

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

    void initiate(const std::size_t sizeAreaMin,
                  const std::size_t sizeMemoryMax);
    void dispose() noexcept;
    area_info allocate(std::size_t sizeArea);
    void deallocate(area_info & target);

	std::size_t getSizeAreaMin();
	std::size_t getSizeMemoryMax();
	std::size_t getSizeAllocated();
}
