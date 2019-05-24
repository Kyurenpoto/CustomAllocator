#include "stdafx.h"

#include "includes/area_allocator/area_manager.h"
#include "includes/area_allocator/virtual_memory_wrapper.h"

namespace
{
    constexpr std::size_t SIZE_CACHE_LINE = 64;
    constexpr std::size_t CNT_PAGE_MIN = 8;

    struct chunk_header
    {
        std::size_t _idChunk;
        std::size_t _sizeAlign;
        chunk_header * _nextChunk;
        chunk_header * _prevChunk;
    };

    struct area_header
    {
        std::size_t _idArea;
        std::size_t _cntChunkTotal;
        std::size_t _cntChunkUsed;
        area_header * _nextArea;
        area_header * _prevArea;
        chunk_header * _activeChunk;
        chunk_header * _inactiveChunk;
    };

    struct area_manage_header
    {
        std::size_t _idManage;
        std::size_t _cntAreaTotal;
        std::size_t _cntAreaUsed;
        area_manage_header * _nextManage;
        area_manage_header * _prevManage;
        area_header * _activeArea;
        area_header * _inactiveArea;
    };
}

area_manager::~area_manager()
{
    dispose();
}

void area_manager::initialize(const uint32_t size)
{
    assert(size > 0);

    _size = size;

    _idNext.resize(static_cast<std::size_t>(size) + 2);
    _idPrev.resize(static_cast<std::size_t>(size) + 2);
    _sizeArea.resize(size);
    _locArea.resize(size);

    _idNext[1] = 1;
}

void area_manager::dispose()
{
    if (_size == 0)
        return;

    while (!isInitialState())
        deallocate(_idNext[1]);

    _size = 0;

    _idNext.resize(0);
    _idPrev.resize(0);
    _sizeArea.resize(0);
    _locArea.resize(0);
}

uint32_t area_manager::allocate(std::size_t nPage)
{
    assert(_size > 0);

    return 0;
}

void area_manager::deallocate(uint32_t id)
{
    assert(_size > 0);

    _sizeArea[id] = 1;
}

const std::size_t area_manager::getSizeArea(const uint32_t id) const noexcept
{
    assert(_size > 0);
    assert(id < _size);

    return _sizeArea[id];
}

bool area_manager::isInitialState() const noexcept
{
    assert(_size > 0);

    return _idNext[1] == 1;
}
