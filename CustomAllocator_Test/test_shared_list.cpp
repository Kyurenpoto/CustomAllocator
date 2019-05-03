#include "pch.h"

#include "../CustomAllocator/shared_list.hpp"

void InitializeZeroSize_Body()
{
    shared_list<1, bool> tmp{ 0 };
}

TEST(SharedListTest, InitializeZeroSize)
{
    ASSERT_DEATH(InitializeZeroSize_Body(), "Assertion failed: size > 0");
}
