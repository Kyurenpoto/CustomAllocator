#pragma once

#include <cstddef>

namespace virtual_memory
{
	void *    reserve(std::size_t nPage);
	void *    commit(void* ptr, std::size_t nPage);
	void      release(void* ptr);
	void      decommit(void* ptr, std::size_t nPage);
}
