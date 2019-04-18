#include "stdafx.h"

#include "page_allocator.h"

namespace
{
	constexpr std::size_t PAGE_SIZE = 4 * 1024;
}

void * page_allocator::reserve(std::size_t nPage)
{
	void * reserved =  VirtualAlloc(nullptr, nPage * PAGE_SIZE, MEM_RESERVE, PAGE_READWRITE);
	
	if (reserved == nullptr)
	{
        abort();
	}

    return reserved;
}

void * page_allocator::commit(void * ptr, std::size_t nPage)
{
    void * commited = VirtualAlloc(ptr, nPage * PAGE_SIZE, MEM_COMMIT, PAGE_READWRITE);
    
    if (commited == nullptr)
    {
        abort();
    }

    return commited;
}

void page_allocator::release(void * ptr)
{
    if (VirtualFree(ptr, 0, MEM_RELEASE) == 0)
    {
        abort();
    }
}

void page_allocator::decommit(void * ptr, std::size_t nPage)
{
    if (VirtualFree(ptr, nPage * PAGE_SIZE, MEM_DECOMMIT) == 0)
    {
        abort();
    }
}
