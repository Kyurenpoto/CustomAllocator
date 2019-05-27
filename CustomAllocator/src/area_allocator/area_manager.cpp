#include "stdafx.h"

#include "includes/area_allocator/area_manager.h"
#include "includes/area_allocator/virtual_memory_wrapper.h"

namespace
{
    constexpr std::size_t SIZE_CACHE_LINE = 64;
    constexpr std::size_t SIZE_PAGE_MIN = 4 * 1024;
    constexpr std::size_t SIZE_AREA_MANAGER = 2 * 1024 * 1024;
    constexpr std::size_t CNT_PAGE_AREA_MANAGER =
        SIZE_AREA_MANAGER / SIZE_PAGE_MIN;

    struct cache_line
    {
        char data[SIZE_CACHE_LINE];
    };

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

    constexpr std::size_t CNT_CHUNK_AREA_MANAGER = 
        SIZE_AREA_MANAGER / SIZE_CACHE_LINE - 3;

    void initAreaManager(area_manage_header * memory, std::size_t id)
    {
        assert(virtual_memory::getAddrInfo(memory).nPage >=
               CNT_PAGE_AREA_MANAGER);

        auto * tmp = reinterpret_cast<cache_line *>(memory);
        std::fill_n(tmp, CNT_CHUNK_AREA_MANAGER + 3, 0);

        memory->_idManage = id;
        memory->_cntAreaTotal = CNT_CHUNK_AREA_MANAGER;
        memory->_cntAreaUsed = 0;
        memory->_nextManage = memory->_prevManage = memory;
        memory->_activeArea = reinterpret_cast<area_header *>(
                                  reinterpret_cast<cache_line*>(memory) + 1);
        memory->_inactiveArea = reinterpret_cast<area_header*>(
                                    reinterpret_cast<cache_line*>(memory) + 2);
    }
}

area_manager::~area_manager()
{
    dispose();
}

void area_manager::initialize(const uint32_t size)
{
}

void area_manager::initialize()
{
    _areas = virtual_memory::alloc(CNT_PAGE_AREA_MANAGER);
}

void area_manager::dispose()
{
    virtual_memory::dealloc(_areas);
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
