#pragma once

#include "../shared_list.hpp"

#include <cassert>

template<uint32_t N, class T>
shared_list<N, T>::~shared_list()
{
    dispose();
}

template<uint32_t N, class T>
void shared_list<N, T>::initialize(const uint32_t size)
{
    assert(size > 0);

    _size = size;

    idNext = new uint32_t[size];
    idPrev = new uint32_t[size];
    data = new T[size];
}

template<uint32_t N, class T>
void shared_list<N, T>::dispose()
{
    if (_size == 0)
        return;

    delete[] idNext;
    delete[] idPrev;
    delete[] data;
}
