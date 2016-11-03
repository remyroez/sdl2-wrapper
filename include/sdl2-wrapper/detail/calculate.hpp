/*
	sdl2-wrapper - C++ wrapper for SDL2
	Copyright (c) 2016 Remy Roez <remyroez@gmail.com>

	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this software must not be misrepresented; you must not
		claim that you wrote the original software. If you use this software
		in a product, an acknowledgment in the product documentation would be
		appreciated but is not required.
	2. Altered source versions must be plainly marked as such, and must not be
		misrepresented as being the original software.
	3. This notice may not be removed or altered from any source distribution.
 */

#ifndef SDL2_WRAPPER_DETAIL_CALCULATE_HPP_
#define SDL2_WRAPPER_DETAIL_CALCULATE_HPP_

#include <limits>
#include <algorithm>
#include <type_traits>

namespace sdl { namespace detail {

template <typename T, typename U = T>
struct calculate final {
	using base_type = T;
	using work_type = U;

	static constexpr base_type min() { return std::numeric_limits<base_type>::min(); }
	static constexpr base_type max() { return std::numeric_limits<base_type>::max(); }

	template <typename T> 
	static constexpr T work_min() { return static_cast<T>(min()); }

	template <typename T>
	static constexpr T work_max() { return static_cast<T>(max()); }

	template <typename T, typename U>
	using bigger_type = std::conditional_t<sizeof(T) >= sizeof(U), T, U>;

	template <typename T, typename U>
	using floating_point_type = std::conditional_t<std::is_floating_point<T>::value, T, U>;

	template <typename T, typename U, typename V = bigger_type<T, U>>
	using bigger_floating_point_type = std::conditional_t<
		std::is_floating_point<T>::value && std::is_floating_point<U>::value,
		V,
		floating_point_type<T, floating_point_type<U, V>>
	>;

	template <typename A = base_type, typename B = A, typename C = bigger_floating_point_type<work_type, decltype(A(0) * B(0))>>
	static constexpr base_type add(A a, B b) noexcept {
		return static_cast<base_type>(std::min(static_cast<C>(a) + b, work_max<C>()));
	}

	template <typename A = base_type, typename B = A, typename C = bigger_floating_point_type<work_type, decltype(A(0) * B(0))>>
	static constexpr base_type sub(A a, B b) noexcept {
		return static_cast<base_type>(std::max(static_cast<C>(a) - b, work_min<C>()));
	}

	template <typename A = base_type, typename B = A, typename C = bigger_floating_point_type<work_type, decltype(A(0) * B(0))>>
	static constexpr base_type mul(A a, B b) noexcept {
		return static_cast<base_type>(std::max(work_min<C>(), std::min(static_cast<C>(a) * b, work_max<C>())));
	}

	template <typename A = base_type, typename B = A, typename C = bigger_floating_point_type<work_type, decltype(A(0) * B(0))>>
	static constexpr base_type div(A a, B b) noexcept {
		return static_cast<base_type>(std::max(work_min<C>(), std::min(static_cast<C>(a) / b, work_max<C>())));
	}
};

} } // namespace sdl::detail

#endif // SDL2_WRAPPER_DETAIL_CALCULATE_HPP_

