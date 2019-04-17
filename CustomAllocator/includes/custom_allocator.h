#pragma once

#include <cstddef>

template<class T>
struct custom_allocator
{
	using value_type = T;

	constexpr custom_allocator() noexcept = default;

	constexpr custom_allocator(const custom_allocator &) noexcept
	{}

	template<class U>
	constexpr custom_allocator(const custom_allocator<U> &) noexcept
	{}

	virtual ~custom_allocator() = default;

	template<class U>
	struct rebind
	{
		using other = custom_allocator<U>;
	};

	[[nodiscard]] T* allocate(std::size_t n);

	void deallocate(T* p, std::size_t n);
};
