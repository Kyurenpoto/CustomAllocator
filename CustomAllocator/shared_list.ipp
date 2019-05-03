#pragma once

#include "shared_list.hpp"

#include <cstdint>

template<uint32_t N, class T>
shared_list<N, T>::shared_list(const uint32_t size) :
    _size(size)
{
    assert(size > 0);
}

template<uint32_t N, class T>
shared_list<N, T>::~shared_list()
{
}
