#include "stdafx.h"

#include "includes/area_allocator/area_manager.h"

area_manager::~area_manager()
{
    dispose();
}

void area_manager::initialize(const uint32_t size)
{
    assert(size > 0);

    _size = size;

    _idNext.resize(size);
    _idPrev.resize(size);
    _areas.resize(size);

    _idNext[1] = 1;
}

void area_manager::dispose()
{
    if (_size == 0)
        return;

    while (!isInitialState())
        deallocate(_idNext[1]);

    _size = 0;
}

uint32_t area_manager::allocate(std::size_t nPage)
{
    assert(_size > 0);

    return 0;
}

void area_manager::deallocate(uint32_t id)
{
    assert(_size > 0);
}

const AreaAllocator::memory_area &
area_manager::operator [] (const uint32_t id) const
{
    assert(_size > 0);
    assert(id < _size);
    assert(_areas[id].size > 0);

    return _areas[id];
}

bool area_manager::isInitialState()
{
    assert(_size > 0);

    return _idNext[1] == 1;
}
