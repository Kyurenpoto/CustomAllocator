#include "pch.h"

#include "../CustomAllocator/includes/area_allocator/area_manager.h"

void InitializeZeroSize_Body()
{
    area_manager tmp;

    tmp.initialize(0);
}

TEST(AreaManagerTest, InitializeZeroSize)
{
    ASSERT_DEATH(InitializeZeroSize_Body(), "Assertion failed: size > 0");
}

TEST(AreaManagerTest, IsInitialized)
{
    area_manager man;

    man.initialize(1);
    
    ASSERT_EXIT(man.getSizeArea(0); exit(0), testing::ExitedWithCode(0), "");

    man.dispose();
}

TEST(AreaManagerTest, IsDisposed)
{
    area_manager man;

    man.initialize(1);

    man.dispose();

    ASSERT_DEATH(man.getSizeArea(0), "Assertion failed: _size > 0");
}

TEST(AreaManagerTest, IsAllocated)
{
    area_manager man;

    man.initialize(1);

    auto id = man.allocate(16);
    auto size = man.getSizeArea(id);
    man.deallocate(id);

    man.dispose();

    ASSERT_EQ(size == 0, false);
}

TEST(AreaManagerTest, IsDeallocated)
{
    area_manager man;

    man.initialize(1);

    auto id = man.allocate(16);
    man.deallocate(id);
    auto size = man.getSizeArea(id);

    man.dispose();

    ASSERT_EQ(size == 0, true);
}
