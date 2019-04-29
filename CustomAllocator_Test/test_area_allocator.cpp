#include "pch.h"

#include "../CustomAllocator/area_allocator.h"

namespace
{
	constexpr std::size_t SIZE_AREA = 16ull * 1024 * 1024;
	constexpr std::size_t SIZE_MEMORY = 4ull * 1024 * 1024 * 1024;
}

TEST(AreaAllocatorTest, isInitiated)
{
    ASSERT_DEATH(AreaAllocator::Initiate(SIZE_AREA, SIZE_MEMORY), "Error on line .*");

	std::size_t sizeAreaMin = AreaAllocator::getSizeAreaMin();
	std::size_t sizeMemoryMax = AreaAllocator::getSizeMemoryMax();

	AreaAllocator::Dispose();

	ASSERT_EQ(sizeAreaMin, SIZE_AREA);
    ASSERT_EQ(sizeMemoryMax, SIZE_MEMORY);
}

TEST(AreaAllocatorTest, isAlreadyInitiated)
{
    AreaAllocator::Initiate(SIZE_AREA, SIZE_MEMORY);
    
    ASSERT_DEATH(AreaAllocator::Initiate(SIZE_AREA, SIZE_MEMORY), "*");

    AreaAllocator::Dispose();
}

TEST(AreaAllocatorTest, isDisposed)
{
    AreaAllocator::Initiate(SIZE_AREA, SIZE_MEMORY);

    ASSERT_DEATH(AreaAllocator::Dispose(), "*");

    std::size_t sizeAreaMin = AreaAllocator::getSizeAreaMin();
    std::size_t sizeMemoryMax = AreaAllocator::getSizeMemoryMax();

    ASSERT_EQ(sizeAreaMin, 0);
    ASSERT_EQ(sizeMemoryMax, 0);
}
