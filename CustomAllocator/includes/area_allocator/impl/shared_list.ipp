#pragma once

#include "../shared_list.hpp"
#include <cassert>

#include <cstdint>

template<uint32_t N, class T>
shared_list<N, T>::shared_list(const uint32_t size) :
    _size(size)
{
    assert(size > 0);

    idNext = new uint32_t[size];
    idPrev = new uint32_t[size];
    data = new T[size];
}

template<uint32_t N, class T>
shared_list<N, T>::~shared_list()
{
    delete[] idNext;
    delete[] idPrev;
    delete[] data;
}
