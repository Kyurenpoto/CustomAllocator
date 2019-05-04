#include "pch.h"

#include "../CustomAllocator/includes/area_allocator/shared_list.hpp"

void InitializeZeroSize_Body()
{
    shared_list<1, bool> tmp;

    tmp.initialize(0);
}

TEST(SharedListTest, InitializeZeroSize)
{
    ASSERT_DEATH(InitializeZeroSize_Body(), "Assertion failed: size > 0");
}