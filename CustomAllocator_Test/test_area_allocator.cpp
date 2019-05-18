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
        AreaAllocator::dispose();
    }
};

TEST_F(AreaAllocatorTest, isInitialized)
{
    ASSERT_NO_THROW(AreaAllocator::initiate(SIZE_AREA, SIZE_MEMORY));

	std::size_t sizeAreaMin = AreaAllocator::getSizeAreaMin();
	std::size_t sizeMemoryMax = AreaAllocator::getSizeMemoryMax();

	AreaAllocator::dispose();

	ASSERT_EQ(sizeAreaMin, SIZE_AREA);
    ASSERT_EQ(sizeMemoryMax, SIZE_MEMORY);
}

TEST_F(AreaAllocatorTest, isAlreadyInitialized)
{
    AreaAllocator::initiate(SIZE_AREA, SIZE_MEMORY);
    
    ASSERT_THROW(AreaAllocator::initiate(SIZE_AREA, SIZE_MEMORY),
                 AreaAllocator::allocator_already_initiated);
}

TEST_F(AreaAllocatorTest, isDisposed)
{
    AreaAllocator::initiate(SIZE_AREA, SIZE_MEMORY);

    ASSERT_NO_THROW(AreaAllocator::dispose());

    std::size_t sizeAreaMin = AreaAllocator::getSizeAreaMin();
    std::size_t sizeMemoryMax = AreaAllocator::getSizeMemoryMax();

    ASSERT_EQ(sizeAreaMin, 0);
    ASSERT_EQ(sizeMemoryMax, 0);
}
