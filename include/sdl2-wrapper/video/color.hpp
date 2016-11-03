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
	using element_type = Uint8;

	static constexpr element_type min = std::numeric_limits<element_type>::min();
	static constexpr element_type max = std::numeric_limits<element_type>::max();

	constexpr color() noexcept : SDL_Color{ min, min, min, max } {}
	constexpr color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = max) noexcept : SDL_Color{ r, g, b, a } {}
	constexpr color(const color &rhs) noexcept = default;
	constexpr color(const SDL_Color &rhs) noexcept : SDL_Color{ rhs.r, rhs.g, rhs.b, rhs.a } {}

public:
	constexpr bool operator ==(const color &rhs) const noexcept { return (r == rhs.r) && (g == rhs.g) && (b == rhs.b) && (a == rhs.a); }

	constexpr bool operator !=(const color &rhs) const noexcept { return !(*this == rhs); }

	constexpr bool operator <(const color &rhs) const noexcept { return (r < rhs.r) && (g < rhs.g) && (b < rhs.b) && (a < rhs.a); }

	constexpr bool operator >(const color &rhs) const noexcept { return (r > rhs.r) && (g > rhs.g) && (b > rhs.b) && (a > rhs.a); }

	constexpr bool operator <=(const color &rhs) const noexcept { return (r <= rhs.r) && (g <= rhs.g) && (b <= rhs.b) && (a <= rhs.a); }

	constexpr bool operator >=(const color &rhs) const noexcept { return (r >= rhs.r) && (g >= rhs.g) && (b >= rhs.b) && (a >= rhs.a); }

	color &operator =(const color &rhs) noexcept { r = rhs.r; g = rhs.g; b = rhs.b; a = rhs.a; return *this; }

	color operator +(const color &rhs) noexcept {
		return{ add_element(r, rhs.r), add_element(g, rhs.g), add_element(b, rhs.b), add_element(a, rhs.a) };
	}

	color operator -(const color &rhs) noexcept {
		return{ sub_element(r, rhs.r), sub_element(g, rhs.g), sub_element(b, rhs.b), sub_element(a, rhs.a) };
	}

	color operator *(const color &rhs) noexcept {
		return{ mul_element(r, rhs.r), mul_element(g, rhs.g), mul_element(b, rhs.b), mul_element(a, rhs.a) };
	}

	color operator *(const element_type scale) noexcept {
		return{ mul_element(r, scale), mul_element(g, scale), mul_element(b, scale), mul_element(a, scale) };
	}

	color operator *(const float scale) noexcept {
		return{ mul_element(r, scale), mul_element(g, scale), mul_element(b, scale), mul_element(a, scale) };
	}

	color operator /(const color &rhs) noexcept {
		return{ div_element(r, rhs.r), div_element(g, rhs.g), div_element(b, rhs.b), div_element(a, rhs.a) };
	}

	color operator /(const element_type scale) noexcept {
		return{ div_element(r, scale), div_element(g, scale), div_element(b, scale), div_element(a, scale) };
	}

	color operator /(const float scale) noexcept {
		return{ div_element(r, scale), div_element(g, scale), div_element(b, scale), div_element(a, scale) };
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
	using calcurate_type = decltype(max * max);

	static constexpr calcurate_type calc_min = min;
	static constexpr calcurate_type calc_max = max;

	using real_type = float;

	static constexpr real_type real_min = min;
	static constexpr real_type real_max = max;

	static constexpr element_type add_element(element_type a, element_type b) noexcept {
		return static_cast<element_type>(std::min(a + b, calc_max));
	}

	static constexpr element_type sub_element(element_type a, element_type b) noexcept {
		return static_cast<element_type>(std::max(a - b, calc_min));
	}

	static constexpr element_type mul_element(element_type a, element_type b) noexcept {
		return static_cast<element_type>(std::max(calc_min, std::min(a * b, calc_max)));
	}

	static constexpr element_type mul_element(element_type a, real_type b) noexcept {
		return static_cast<element_type>(std::max(calc_min, std::min(static_cast<calcurate_type>(a * b), calc_max)));
	}

	static constexpr element_type div_element(element_type a, element_type b) noexcept {
		return static_cast<element_type>(std::max(real_min, std::min(static_cast<real_type>(a) * b, real_max)));
	}

	static constexpr element_type div_element(element_type a, real_type b) noexcept {
		return static_cast<element_type>(std::max(real_min, std::min(a * b, real_max)));
	}
};

} } // namespace sdl::video

#endif // SDL2_WRAPPER_VIDEO_COLOR_HPP_

