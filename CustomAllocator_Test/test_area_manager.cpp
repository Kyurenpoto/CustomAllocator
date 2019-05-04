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
