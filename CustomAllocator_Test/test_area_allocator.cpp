#include "pch.h"

#include "../CustomAllocator/includes/area_allocator/area_allocator.h"

namespace
{
	constexpr std::size_t SIZE_AREA = 16ull * 1024 * 1024;
	constexpr std::size_t SIZE_MEMORY = 4ull * 1024 * 1024 * 1024;
}

class AreaAllocatorTest :
    public testing::Test
{
protected:
    virtual void SetUp()
    {
        area_allocator::dispose();
    }
};

TEST_F(AreaAllocatorTest, isInitialized)
{
    ASSERT_NO_THROW(area_allocator::initiate(SIZE_AREA, SIZE_MEMORY));

	std::size_t sizeAreaMin = area_allocator::getSizeAreaMin();
	std::size_t sizeMemoryMax = area_allocator::getSizeMemoryMax();

	area_allocator::dispose();

	ASSERT_EQ(sizeAreaMin, SIZE_AREA);
    ASSERT_EQ(sizeMemoryMax, SIZE_MEMORY);
}

TEST_F(AreaAllocatorTest, isAlreadyInitialized)
{
    area_allocator::initiate(SIZE_AREA, SIZE_MEMORY);
    
    ASSERT_THROW(area_allocator::initiate(SIZE_AREA, SIZE_MEMORY),
                 area_allocator::allocator_already_initiated);
}

TEST_F(AreaAllocatorTest, isDisposed)
{
    area_allocator::initiate(SIZE_AREA, SIZE_MEMORY);

    ASSERT_NO_THROW(area_allocator::dispose());

    std::size_t sizeAreaMin = area_allocator::getSizeAreaMin();
    std::size_t sizeMemoryMax = area_allocator::getSizeMemoryMax();

    ASSERT_EQ(sizeAreaMin, 0);
    ASSERT_EQ(sizeMemoryMax, 0);
}
