#pragma once

#include <cstdint>
#include <cstddef>

struct page_allocator
{
	static void *    reserve(std::size_t nPage);
	static void *    commit(void * ptr, std::size_t nPage);
	static void      release(void * ptr);
	static void      decommit(void * ptr, std::size_t nPage);

private:
	static std::size_t    _reserved;
	static std::size_t    _commited;
	static std::size_t    _used;
	static std::size_t    _limit;

	static void *         _begin;
	static void *         _end;
};
