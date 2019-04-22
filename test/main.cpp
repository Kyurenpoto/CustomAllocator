#include <iostream>
#include <chrono>
#include <thread>

#include "../CustomAllocator/virtual_memory_wrapper.h"

using namespace std::chrono_literals;

int main()
{
    auto addr = virtual_memory_wrapper::reserve(16);

    std::cout << "Reserve\n";
    std::this_thread::sleep_for(10s);

    virtual_memory_wrapper::release(addr);

    std::cout << "Release\n";
    std::this_thread::sleep_for(10s);

    std::cout << "Test Complete\n";
}
