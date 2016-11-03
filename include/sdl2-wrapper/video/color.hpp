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

#ifndef SDL2_WRAPPER_VIDEO_COLOR_HPP_
#define SDL2_WRAPPER_VIDEO_COLOR_HPP_

#include <limits>
#include <algorithm>

namespace sdl { inline namespace video {

struct color : public SDL_Color {
	using element_type = decltype(SDL_Color::r);
	using real_type = float;

	static constexpr element_type min = std::numeric_limits<element_type>::min();
	static constexpr element_type max = std::numeric_limits<element_type>::max();

	constexpr color() noexcept : SDL_Color{ min, min, min, max } {}
	constexpr color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = max) noexcept : SDL_Color{ r, g, b, a } {}
	constexpr color(const color &rhs) noexcept = default;
	constexpr color(const SDL_Color &rhs) noexcept : SDL_Color(rhs) {}

public:
	constexpr bool operator ==(const color &rhs) const noexcept { return (r == rhs.r) && (g == rhs.g) && (b == rhs.b) && (a == rhs.a); }
	constexpr bool operator !=(const color &rhs) const noexcept { return !(*this == rhs); }

	constexpr bool operator <(const color &rhs) const noexcept { return (r < rhs.r) && (g < rhs.g) && (b < rhs.b) && (a < rhs.a); }
	constexpr bool operator >(const color &rhs) const noexcept { return (r > rhs.r) && (g > rhs.g) && (b > rhs.b) && (a > rhs.a); }

	constexpr bool operator <=(const color &rhs) const noexcept { return (r <= rhs.r) && (g <= rhs.g) && (b <= rhs.b) && (a <= rhs.a); }
	constexpr bool operator >=(const color &rhs) const noexcept { return (r >= rhs.r) && (g >= rhs.g) && (b >= rhs.b) && (a >= rhs.a); }

	color &operator =(const color &rhs) noexcept { r = rhs.r; g = rhs.g; b = rhs.b; a = rhs.a; return *this; }

	color operator +(const color &rhs) noexcept {
		return{ calculate::add(r, rhs.r), calculate::add(g, rhs.g), calculate::add(b, rhs.b), calculate::add(a, rhs.a) };
	}

	color operator -(const color &rhs) noexcept {
		return{ calculate::sub(r, rhs.r), calculate::sub(g, rhs.g), calculate::sub(b, rhs.b), calculate::sub(a, rhs.a) };
	}

	color operator *(const color &rhs) noexcept {
		return{ calculate::mul(r, rhs.r), calculate::mul(g, rhs.g), calculate::mul(b, rhs.b), calculate::mul(a, rhs.a) };
	}

	color operator *(const element_type scale) noexcept {
		return{ calculate::mul(r, scale), calculate::mul(g, scale), calculate::mul(b, scale), calculate::mul(a, scale) };
	}

	color operator *(const real_type scale) noexcept {
		return{ calculate::mul(r, scale), calculate::mul(g, scale), calculate::mul(b, scale), calculate::mul(a, scale) };
	}

	color operator /(const color &rhs) noexcept {
		return{ calculate::div(r, rhs.r), calculate::div(g, rhs.g), calculate::div(b, rhs.b), calculate::div(a, rhs.a) };
	}

	color operator /(const element_type scale) noexcept {
		return{ calculate::div(r, scale), calculate::div(g, scale), calculate::div(b, scale), calculate::div(a, scale) };
	}

	color operator /(const real_type scale) noexcept {
		return{ calculate::div(r, scale), calculate::div(g, scale), calculate::div(b, scale), calculate::div(a, scale) };
	}

	color &operator +=(const color &rhs) noexcept { return *this = (*this + rhs); }
	color &operator -=(const color &rhs) noexcept { return *this = (*this - rhs); }
	color &operator *=(const color &rhs) noexcept { return *this = (*this * rhs); }
	color &operator *=(const element_type scale) noexcept { return *this = (*this * scale); }
	color &operator *=(const float scale) noexcept { return *this = (*this * scale); }
	color &operator /=(const color &rhs) noexcept { return *this = (*this / rhs); }
	color &operator /=(const element_type scale) noexcept { return *this = (*this / scale); }
	color &operator /=(const float scale) noexcept { return *this = (*this / scale); }

public:
	static constexpr color transparent() noexcept { return{ min, min, min, min }; }

	static constexpr color black() noexcept { return{ min, min, min, max }; }

	static constexpr color red() noexcept { return{ max, min, min, max }; }
	static constexpr color green() noexcept { return{ min, max, min, max }; }
	static constexpr color blue() noexcept { return{ min, min, max, max }; }

	static constexpr color yellow() noexcept { return{ max, max, min, max }; }
	static constexpr color magenta() noexcept { return{ max, min, max, max }; }
	static constexpr color cyan() noexcept { return{ min, max, max, max }; }

	static constexpr color white() noexcept { return{ max, max, max, max }; }

protected:
	using calculate = sdl::detail::calculate<element_type, decltype(max * max)>;
};

} } // namespace sdl::video

#endif // SDL2_WRAPPER_VIDEO_COLOR_HPP_

