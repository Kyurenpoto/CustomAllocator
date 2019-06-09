#include "stdafx.h"

#include "includes/area_allocator/area_manager.h"
#include "includes/area_allocator/virtual_memory_wrapper.h"

#include <array>

#include <gsl.h>

namespace
{
    constexpr std::size_t SIZE_CACHE_LINE = 64;
    constexpr std::size_t SIZE_PAGE_MIN = 4 * 1024;

    void initMemory(void * memory, const std::size_t size) noexcept
    {
        assert(memory != nullptr);
        assert(virtual_memory::getAddrInfo(memory).nPage >= size);

        std::memset(memory, 0, size);
    }

    struct chunk_header
    {
        area_header *     _area;

        uint32_t          _idChunk;
        uint8_t           _isAlive;
        uint8_t           _typeHeader : 4,
                          _typeChunk  : 4;
        uint8_t           _sizeChunk;
        uint8_t           _sizeAlign;

        uint32_t          _next;
        uint32_t          _prev;
        uint32_t          _begin;
        uint32_t          _end;
    };

    template<std::size_t N>
    struct internal_chunk
    {
        std::array<std::byte, N> data;
    };

    struct lfe_chunk_64
    {
        chunk_header                        _header;

        std::array<internal_chunk<1>, 8>    _chunk_1;
        std::array<internal_chunk<2>, 4>    _chunk_2;
        std::array<internal_chunk<4>, 2>    _chunk_4;
        std::array<internal_chunk<8>, 1>    _chunk_8;
    };

    struct lfe_chunk_128
    {
        chunk_header                         _header;

        std::array<internal_chunk<1>, 16>    _chunk_1;
        std::array<internal_chunk<2>,  8>    _chunk_2;
        std::array<internal_chunk<4>,  4>    _chunk_4;
        std::array<internal_chunk<8>,  2>    _chunk_8;
        std::array<internal_chunk<16>, 2>    _chunk_16;
    };

    struct lfe_chunk_256
    {
        chunk_header                         _header;

        std::array<internal_chunk<1>, 32>    _chunk_1;
        std::array<internal_chunk<2>, 16>    _chunk_2;
        std::array<internal_chunk<4>,  8>    _chunk_4;
        std::array<internal_chunk<8>,  4>    _chunk_8;
        std::array<internal_chunk<16>, 2>    _chunk_16;
        std::array<internal_chunk<32>, 2>    _chunk_32;
    };

    struct lfe_chunk_512
    {
        chunk_header                         _header;

        std::array<internal_chunk<1>, 64>    _chunk_1;
        std::array<internal_chunk<2>, 32>    _chunk_2;
        std::array<internal_chunk<4>, 16>    _chunk_4;
        std::array<internal_chunk<8>,  8>    _chunk_8;
        std::array<internal_chunk<16>, 4>    _chunk_16;
        std::array<internal_chunk<32>, 2>    _chunk_32;
        std::array<internal_chunk<64>, 2>    _chunk_64;
    };

    struct pool_chunk
    {
        chunk_header _header;
    };

    struct flexible_chunk
    {
        chunk_header _header;
    };

    struct index_header;

    struct area_header
    {
        gsl::span<std::byte> _chunks;
        index_header * _index;
        
        std::size_t _idArea;
        std::size_t _cntChunkUsed;
        std::size_t _sizeChunk;
    };

    struct index_header
    {
        area_header * _area;
        index_header * _root; // for debuging
        uint32_t _idArea;
        uint32_t _parent;
        uint32_t _left;
        uint32_t _right;
    };

    struct manage_header
    {
        std::size_t _idManage;
        uint32_t _cntAreaUsed;
        uint32_t _cntIndexUsed;
        manage_header * _nextManage;
        manage_header * _prevManage;
    };

    struct manage_area
    {
        static constexpr std::size_t SIZE = 2 * 1024 * 1024;
        static constexpr std::size_t CNT_PAGE = SIZE / SIZE_PAGE_MIN;
        static constexpr std::size_t CNT_CHUNK = SIZE / SIZE_CACHE_LINE * 2 - 1;

        static void initialize(manage_area * area, std::size_t id) noexcept
        {
            initMemory(area, SIZE);

            manage_header * header = &area->_header;

            header->_idManage = id;
            header->_nextManage = header->_prevManage = header;
        }

        static void dispose(manage_area * area) noexcept
        {
            initMemory(area, SIZE);
        }

        bool isOverflow() const noexcept
        {
            return _header._cntAreaUsed < CNT_CHUNK ||
                   _indice.at(1)._root != &_indice.at(1);
        }

        bool isUnderflow() const noexcept
        {
            return _header._cntAreaUsed == 0;
        }

        uint32_t addArea(const area_header * area) const noexcept
        {
            assert(!isOverflow());

            return 0;
        }

        void removeArea(const uint32_t id) const noexcept
        {
            assert(!isUnderflow());
            assert(findArea(id) != nullptr);
        }

        area_header * findArea(const uint32_t id) const noexcept
        {
            assert(!isUnderflow());

            return nullptr;
        }

        manage_header _header;
        std::array<index_header, CNT_CHUNK> _indice;
    };
}

area_manager::~area_manager() noexcept
{
    dispose();
}

void area_manager::initialize() noexcept
{
    assert(_areas == nullptr);

    _areas = virtual_memory::alloc(manage_area::CNT_PAGE);

    manage_area::initialize(static_cast<manage_area*>(_areas), 0);
}

void area_manager::dispose() noexcept
{
    assert(_areas != nullptr);

    manage_area::dispose(static_cast<manage_area*>(_areas));

    virtual_memory::dealloc(_areas);
}

uint32_t area_manager::allocate(std::size_t nPage) noexcept
{
    const manage_area * manager = static_cast<const manage_area *>(_areas);

    assert(manager != nullptr);

    const area_header * area = static_cast<const area_header *>(
                                virtual_memory::alloc(nPage));

    assert(area != nullptr);

    // initialize
    return manager->addArea(area);
}

void area_manager::deallocate(uint32_t id) noexcept
{
    const manage_area * manager = static_cast<const manage_area *>(_areas);
    
    assert(manager != nullptr);

    area_header * area = manager->findArea(id);

    assert(area != nullptr);

    // dispose
    manager->removeArea(id);
    virtual_memory::dealloc(area);
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
