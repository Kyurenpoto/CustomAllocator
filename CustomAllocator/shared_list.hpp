#pragma once

#include <cstdint>

/*
* One or more lists exchange ownership of preallocated nodes.
* This class does not provide operations to add or remove nodes from the entire lists.
*/
template<uint32_t N, class T>
struct shared_list
{
    static_assert(N > 0, "The number of lists must be at least one.");
    static_assert(sizeof(T) > 0, "The size of the type must be greater than zero.");

    shared_list(const uint32_t size);
    shared_list(const shared_list &) = delete;
    shared_list(shared_list &&) = delete;
    shared_list & operator = (const shared_list &) = delete;
    shared_list & operator = (shared_list &&) = delete;
    ~shared_list();

    void move(const uint32_t id, const uint32_t numListTo);

    T * operator [] (const uint32_t id);

private:
    uint32_t _size;
    
    uint32_t * idNext = nullptr;
    uint32_t * idPrev = nullptr;

    T * data = nullptr;
};

#include "shared_list.ipp"
