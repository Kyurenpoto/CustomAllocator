#include "stdafx.h"

#include "virtual_memory_wrapper.h"

namespace
{
	constexpr std::size_t PAGE_SIZE = 4 * 1024;
}

void * virtual_memory::reserve(std::size_t nPage)
{
	void* reserved = VirtualAlloc(nullptr, nPage * PAGE_SIZE, MEM_RESERVE, PAGE_READWRITE);

	if (reserved == nullptr)
	{
		abort();
	}

	return reserved;
}

void * virtual_memory::commit(void * ptr, std::size_t nPage)
{
	void* commited = VirtualAlloc(ptr, nPage * PAGE_SIZE, MEM_COMMIT, PAGE_READWRITE);

	if (commited == nullptr)
	{
		abort();
	}

	return commited;
}

void virtual_memory::release(void * ptr)
{
	if (VirtualFree(ptr, 0, MEM_RELEASE) == 0)
	{
		abort();
	}
}

void virtual_memory::decommit(void * ptr, std::size_t nPage)
{
	if (VirtualFree(ptr, nPage * PAGE_SIZE, MEM_DECOMMIT) == 0)
	{
		abort();
	}
}
