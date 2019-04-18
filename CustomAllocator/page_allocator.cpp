#include "stdafx.h"

#include "page_allocator.h"

namespace
{
	constexpr std::size_t PAGE_SIZE = 4 * 1024;

	void IntentedCrash()
	{
		int * ptr = nullptr;
		int tmp = *ptr;
	}
}

void * page_allocator::reserve(std::size_t nPage)
{
	void * ptr =  VirtualAlloc(nullptr, nPage * PAGE_SIZE, MEM_RESERVE, PAGE_READWRITE);
	
	if (ptr == nullptr)
	{
		IntentedCrash();
	}
	return VirtualAlloc(nullptr, nPage * PAGE_SIZE, MEM_RESERVE, PAGE_READWRITE);
}

void * page_allocator::commit(void * ptr, std::size_t nPage)
{
	return VirtualAlloc(ptr, nPage * PAGE_SIZE, MEM_COMMIT, PAGE_READWRITE);
}

void page_allocator::release(void * ptr)
{
	VirtualFree(ptr, 0, MEM_RELEASE);
}

void page_allocator::decommit(void * ptr, std::size_t nPage)
{
	VirtualFree(ptr, nPage * PAGE_SIZE, MEM_DECOMMIT);
}
