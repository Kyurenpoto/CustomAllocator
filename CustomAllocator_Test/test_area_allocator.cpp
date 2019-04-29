#include "pch.h"

#include "../CustomAllocator/area_allocator.h"

namespace
{
	constexpr std::size_t SIZE_AREA = 16ull * 1024 * 1024;
	constexpr std::size_t SIZE_MEMORY = 4ull * 1024 * 1024 * 1024;
}

TEST(AreaAllocatorTest, isInitiated)
{
	AreaAllocator::Initiate(SIZE_AREA, SIZE_MEMORY);

	std::size_t sizeAreaMin = AreaAllocator::getSizeAreaMin();
	std::size_t sizeMemoryMax = AreaAllocator::getSizeMemoryMax();

	AreaAllocator::Dispose();

	ASSERT_EQ((sizeAreaMin == SIZE_AREA && sizeMemoryMax == SIZE_MEMORY),
		      true);
}
