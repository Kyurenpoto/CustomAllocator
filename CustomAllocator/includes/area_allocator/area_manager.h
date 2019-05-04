#pragma once

#include "memory_area.h"

struct area_manager
{
    area_manager() = default;
    area_manager(const area_manager &) = delete;
    area_manager(area_manager &&) = delete;
    area_manager & operator = (const area_manager &) = delete;
    area_manager & operator = (area_manager &&) = delete;
    ~area_manager();

    void initialize(const uint32_t size);
    void dispose();

    uint32_t allocate(std::size_t nPage);
    void deallocate(uint32_t id);

    const AreaAllocator::memory_area & operator [] (const uint32_t id) const;

private:
    bool isInitialState();

private:
    uint32_t _size = 0;
    
    uint32_t * _idNext = nullptr;
    uint32_t * _idPrev = nullptr;

    AreaAllocator::memory_area * _areas = nullptr;
};
