#include "stdafx.h"

#include "includes/area_allocator/area_info.h"
#include "includes/area_allocator/area_access.h"

std::size_t AreaAllocator::area_info::getSizeTotal() const noexcept
{
    return AreaAccess::getSizeTotal(_areaId);
}

std::size_t AreaAllocator::area_info::getAreaId() const noexcept
{
    return _areaId;
}
