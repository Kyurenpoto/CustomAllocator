#include "stdafx.h"

#include "includes/area_allocator/area_info.h"
#include "includes/area_allocator/area_access.h"

std::size_t area_allocator::area_info::getSizeTotal() const
{
    return area_access::getSizeTotal(_areaId);
}

std::size_t area_allocator::area_info::getAreaId() const noexcept
{
    return _areaId;
}
