#include "stdafx.h"

#include "includes/area_allocator/virtual_memory_wrapper.h"

namespace
{
	constexpr std::size_t PAGE_SIZE = 4 * 1024;
}

void * virtual_memory::reserve(std::size_t nPage)
{
	void* reserved = VirtualAlloc(nullptr, nPage * PAGE_SIZE, MEM_RESERVE, PAGE_READWRITE);

    assert(reserved != nullptr);

	return reserved;
}

void * virtual_memory::commit(void * ptr, std::size_t nPage)
{
	void* commited = VirtualAlloc(ptr, nPage * PAGE_SIZE, MEM_COMMIT, PAGE_READWRITE);

    assert(commited != nullptr);

	return commited;
}

void virtual_memory::release(void * ptr)
{
    assert(VirtualFree(ptr, 0, MEM_RELEASE));
}

void virtual_memory::decommit(void * ptr, std::size_t nPage)
{
    assert(VirtualFree(ptr, nPage * PAGE_SIZE, MEM_DECOMMIT));
}

void* virtual_memory::alloc(std::size_t nPage)
{
    void * ptr = VirtualAlloc(nullptr, nPage * PAGE_SIZE,
                              MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    assert(ptr != nullptr);

    return ptr;
}

void virtual_memory::dealloc(void * ptr, std::size_t nPage)
{
    assert(VirtualFree(ptr, nPage * PAGE_SIZE, MEM_DECOMMIT | MEM_RELEASE));
}
