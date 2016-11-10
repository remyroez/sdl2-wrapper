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

#ifndef SDL2_WRAPPER_DETAIL_TYPE_TRAITS_HPP_
#define SDL2_WRAPPER_DETAIL_TYPE_TRAITS_HPP_

#include <type_traits>

namespace sdl { namespace detail {

template <bool B>
using meta_if = std::conditional_t<B, std::true_type, std::false_type>;

template <typename...>
using void_t = void;

template <typename T>
using concept = std::enable_if<T::value, std::nullptr_t>;

template <typename T>
using concept_t = typename concept<T>::type;

template <typename T, typename U>
using concept_is_same = concept_t<std::is_same<T, U>>;

template <typename T, typename = typename std::is_enum<T>::type>
struct safe_underlying_type { using type = T; };

template <typename T>
struct safe_underlying_type<T, std::true_type> { using type = std::underlying_type_t<T>; };

template <typename T>
using safe_underlying_type_t = typename safe_underlying_type<T>::type;

template <typename T>
constexpr safe_underlying_type_t<T> underlying_cast(T t) noexcept { return static_cast<safe_underlying_type_t<T>>(t); }

} } // namespace sdl::detail

#endif // SDL2_WRAPPER_DETAIL_TYPE_TRAITS_HPP_

