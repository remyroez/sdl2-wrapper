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

#ifndef SDL2_WRAPPER_VIDEO_PIXEL_FORMAT_HPP_
#define SDL2_WRAPPER_VIDEO_PIXEL_FORMAT_HPP_

#include <string>

namespace sdl { inline namespace video {

void calculate_gamma_ramp(float gamma, Uint16 *ramp) noexcept { SDL_CalculateGammaRamp(gamma, ramp); }

class pixel_format final : public sdl::detail::resource<SDL_PixelFormat, decltype(&SDL_FreeFormat)> {
public:
	static auto enum_name(Uint32 format) noexcept { return SDL_GetPixelFormatName(format); }

	static bool enum_to_masks(Uint32 format, int* bpp, Uint32* Rmask, Uint32* Gmask, Uint32* Bmask, Uint32* Amask) noexcept {
		return (SDL_PixelFormatEnumToMasks(format, bpp, Rmask, Gmask, Bmask, Amask) == SDL_TRUE);
	}

	static Uint32 masks_to_enum(int bpp, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) noexcept {
		return SDL_MasksToPixelFormatEnum(bpp, Rmask, Gmask, Bmask, Amask);
	}

	static decltype(auto) make_resource(Uint32 format) {
		return resource::make_resource(SDL_AllocFormat, SDL_FreeFormat, format);
	}

public:
	using pixel_type = Uint32;

	pixel_format() = default;

	explicit pixel_format(Uint32 format)
		: resource(make_resource(format)) {}

	void create(Uint32 format) {
		_handle_holder = make_resource(format);
	}

	auto format() const noexcept { return (valid() ? get()->format : SDL_PIXELFORMAT_UNKNOWN); }

	auto bits_per_pixel() const noexcept { return (valid() ? get()->BitsPerPixel : 0); }
	auto bytes_per_pixel() const noexcept { return (valid() ? get()->BytesPerPixel : 0); }

	auto r_mask() const noexcept { return (valid() ? get()->Rmask : 0); }
	auto g_mask() const noexcept { return (valid() ? get()->Gmask : 0); }
	auto b_mask() const noexcept { return (valid() ? get()->Bmask : 0); }
	auto a_mask() const noexcept { return (valid() ? get()->Amask : 0); }

	auto r_loss() const noexcept { return (valid() ? get()->Rloss : 0); }
	auto g_loss() const noexcept { return (valid() ? get()->Gloss : 0); }
	auto b_loss() const noexcept { return (valid() ? get()->Bloss : 0); }
	auto a_loss() const noexcept { return (valid() ? get()->Aloss : 0); }

	auto r_shift() const noexcept { return (valid() ? get()->Rshift : 0); }
	auto g_shift() const noexcept { return (valid() ? get()->Gshift : 0); }
	auto b_shift() const noexcept { return (valid() ? get()->Bshift : 0); }
	auto a_shift() const noexcept { return (valid() ? get()->Ashift : 0); }

	bool pallete(SDL_Palette *palette) noexcept { return (SDL_SetPixelFormatPalette(get(), palette) == 0); }

	pixel_type map(Uint8 r, Uint8 g, Uint8 b) const noexcept { return SDL_MapRGB(get(), r, g, b); }

	pixel_type map(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const noexcept { return SDL_MapRGBA(get(), r, g, b, a); }

	pixel_type map(const color &color) const noexcept { return map(color.r, color.g, color.b, color.a); }

	pixel_type map_rgb(const color &color) const noexcept { return map(color.r, color.g, color.b); }

	void pixel_color(pixel_type pixel, Uint8 *r, Uint8 *g, Uint8 *b) const noexcept { SDL_GetRGB(pixel, get(), r, g, b); }

	void pixel_color(pixel_type pixel, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a) const noexcept { SDL_GetRGBA(pixel, get(), r, g, b, a); }

	void pixel_color(pixel_type pixel, color &color) const noexcept { pixel_color(pixel, &color.r, &color.g, &color.b, &color.a); }

	color pixel_color(pixel_type pixel) const noexcept { color result; pixel_color(pixel, result); return result; }

	void pixel_color_rgb(pixel_type pixel, color &color) const noexcept { pixel_color(pixel, &color.r, &color.g, &color.b); }

	color pixel_color_rgb(pixel_type pixel) const noexcept { color result; pixel_color_rgb(pixel, result); return result; }
};

} } // namespace sdl::video

#endif // SDL2_WRAPPER_VIDEO_PIXEL_FORMAT_HPP_

