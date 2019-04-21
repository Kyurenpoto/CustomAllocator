#include <iostream>
#include <chrono>
#include <thread>

#include "../CustomAllocator/page_allocator.h"

using namespace std::chrono_literals;

int main()
{
    auto addr = page_allocator::reserve(16);

    std::cout << "Reserve\n";
    std::this_thread::sleep_for(10s);

    page_allocator::release(addr);

    std::cout << "Release\n";
    std::this_thread::sleep_for(10s);

    std::cout << "Test Complete\n";
}
