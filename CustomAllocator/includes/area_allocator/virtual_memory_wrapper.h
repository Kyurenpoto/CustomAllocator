#pragma once

#include <cstddef>

namespace virtual_memory
{
    [[deprecated]]
	void *    reserve(std::size_t nPage);
    [[deprecated]]
	void *    commit(void * ptr, std::size_t nPage);
    [[deprecated]]
	void      release(void * ptr);
    [[deprecated]]
	void      decommit(void* ptr, std::size_t nPage);

    void *    alloc(std::size_t nPage);
    void      dealloc(void* ptr, std::size_t nPage);
}
