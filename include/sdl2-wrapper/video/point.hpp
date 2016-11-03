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

#ifndef SDL2_WRAPPER_VIDEO_POINT_HPP_
#define SDL2_WRAPPER_VIDEO_POINT_HPP_

#include <limits>
#include <algorithm>

namespace sdl { inline namespace video {

struct point : public SDL_Point {
	using element_type = decltype(SDL_Point::x);
	using real_type = float;

public:
	constexpr point() : SDL_Point{ 0, 0 } {}
	constexpr point(int x, int y) : SDL_Point{ x, y } {}
	constexpr point(const point &rhs) = default;
	constexpr point(const SDL_Point &rhs) : SDL_Point(rhs) {}

public:
	constexpr bool operator ==(const point &rhs) const noexcept { return (x == rhs.x) && (y == rhs.y); }
	constexpr bool operator !=(const point &rhs) const noexcept { return !(*this == rhs); }

	constexpr bool operator <(const point &rhs) const noexcept { return (x < rhs.x) && (y < rhs.y); }
	constexpr bool operator >(const point &rhs) const noexcept { return (x > rhs.x) && (y > rhs.y); }

	constexpr bool operator <=(const point &rhs) const noexcept { return (x <= rhs.x) && (y <= rhs.y); }
	constexpr bool operator >=(const point &rhs) const noexcept { return (x >= rhs.x) && (y >= rhs.y); }

	point &operator =(const point &rhs) noexcept { x = rhs.x; y = rhs.y; return *this; }

	constexpr point operator +(const point &rhs) const noexcept {
		return{ calculate::add(x, rhs.x), calculate::add(y, rhs.y) };
	}

	constexpr point operator -(const point &rhs) const noexcept {
		return{ calculate::sub(x, rhs.x), calculate::sub(y, rhs.y) };
	}

	constexpr point operator *(const element_type scale) const noexcept {
		return{ calculate::mul(x, scale), calculate::mul(y, scale) };
	}

	constexpr point operator *(const real_type scale) const noexcept {
		return{ calculate::mul(x, scale), calculate::mul(y, scale) };
	}

	constexpr point operator /(const element_type scale) const noexcept {
		return{ calculate::div(x, scale), calculate::div(y, scale) };
	}

	constexpr point operator /(const real_type scale) const noexcept {
		return{ calculate::div(x, scale), calculate::div(y, scale) };
	}

	point &operator +=(const point &rhs) noexcept { return *this = (*this + rhs); }
	point &operator -=(const point &rhs) noexcept { return *this = (*this - rhs); }
	point &operator *=(const element_type scale) noexcept { return *this = (*this * scale); }
	point &operator *=(const float scale) noexcept { return *this = (*this * scale); }
	point &operator /=(const element_type scale) noexcept { return *this = (*this / scale); }
	point &operator /=(const float scale) noexcept { return *this = (*this / scale); }

protected:
	using calculate = sdl::detail::calculate<element_type, Sint64>;
};

} } // namespace sdl::video

#endif // SDL2_WRAPPER_VIDEO_POINT_HPP_

