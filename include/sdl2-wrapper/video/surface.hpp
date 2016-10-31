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

#ifndef SDL2_WRAPPER_VIDEO_SURFACE_HPP_
#define SDL2_WRAPPER_VIDEO_SURFACE_HPP_

#include "../util.hpp"

namespace sdl { inline namespace video {

bool convert_pixels(
	int width,
	int height,
	Uint32 src_format,
	const void *src,
	int src_pitch,
	Uint32 dst_format,
	void *dst,
	int dst_pitch
) noexcept {
	return (SDL_ConvertPixels(width, height, src_format, src, src_pitch, dst_format, dst, dst_pitch) == 0);
}

class surface {
public:
	using resource_t = SDL_Surface;

	using resource_ptr = resource_t *;

	using handle = std::unique_ptr<resource_t, decltype(&SDL_FreeSurface)>;

	template<bool b>
	struct basic_mask {};

	template<>
	struct basic_mask<true> {
		static constexpr Uint32 red = 0xff000000;
		static constexpr Uint32 green = 0x00ff0000;
		static constexpr Uint32 blue = 0x0000ff00;
		static constexpr Uint32 alpha = 0x000000ff;
	};

	template<>
	struct basic_mask<false> {
		static constexpr Uint32 red = 0x000000ff;
		static constexpr Uint32 green = 0x0000ff00;
		static constexpr Uint32 blue = 0x00ff0000;
		static constexpr Uint32 alpha = 0xff000000;
	};

	using mask = basic_mask<sdl::is_big_endian>;

	static handle make_resource(Uint32 flags, int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) {
		return sdl::detail::make_resource(SDL_CreateRGBSurface, SDL_FreeSurface, flags, width, height, depth, Rmask, Gmask, Bmask, Amask);
	}

	static handle make_resource(void* pixels, int width, int height, int depth, int pitch, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) {
		return sdl::detail::make_resource(SDL_CreateRGBSurfaceFrom, SDL_FreeSurface, pixels, width, height, depth, pitch, Rmask, Gmask, Bmask, Amask);
	}

	static handle make_resource(Uint32 flags, int width, int height, int depth, Uint32 format) {
		return sdl::detail::make_resource(SDL_CreateRGBSurfaceWithFormat, SDL_FreeSurface, flags, width, height, depth, format);
	}

	static handle make_resource(void* pixels, int width, int height, int depth, int pitch, Uint32 format) {
		return sdl::detail::make_resource(SDL_CreateRGBSurfaceWithFormatFrom, SDL_FreeSurface, pixels, width, height, depth, pitch, format);
	}

	static handle make_resource(const char* file) {
		return handle(SDL_LoadBMP(file), SDL_FreeSurface);
	}

	static handle make_resource(SDL_RWops* src, int freesrc) {
		return sdl::detail::make_resource(SDL_LoadBMP_RW, SDL_FreeSurface, src, freesrc);
	}

	explicit surface(Uint32 flags, int width, int height, int depth)
		: _handle(make_resource(flags, width, height, depth, mask::red, mask::green, mask::blue, mask::alpha)) {}

	explicit surface(void* pixels, int width, int height, int depth, int pitch)
		: _handle(make_resource(pixels, width, height, depth, pitch, mask::red, mask::green, mask::blue, mask::alpha)) {}

	explicit surface(Uint32 flags, int width, int height, int depth, Uint32 format)
		: _handle(make_resource(flags, width, height, depth, format)) {}

	explicit surface(void* pixels, int width, int height, int depth, int pitch, Uint32 format)
		: _handle(make_resource(pixels, width, height, depth, pitch, format)) {}

	explicit surface(const char* file)
		: _handle(make_resource(file)) {}

	explicit surface(SDL_RWops* src, int freesrc)
		: _handle(make_resource(src, freesrc)) {}

	resource_ptr get() const noexcept { return _handle.get(); }

	bool valid() const noexcept { return (get() != nullptr); }

	explicit operator bool() const { return valid(); }

	operator resource_ptr() const { return get(); }

	void create(Uint32 flags, int width, int height, int depth) {
		_handle = std::move(make_resource(flags, width, height, depth, mask::red, mask::green, mask::blue, mask::alpha));
	}

	void create_from(void* pixels, int width, int height, int depth, int pitch) {
		_handle = std::move(make_resource(pixels, width, height, depth, pitch, mask::red, mask::green, mask::blue, mask::alpha));
	}

	void create_with_format(Uint32 flags, int width, int height, int depth, Uint32 format) {
		_handle = std::move(make_resource(flags, width, height, depth, format));
	}

	void create_with_format_from(void* pixels, int width, int height, int depth, int pitch, Uint32 format) {
		_handle = std::move(make_resource(pixels, width, height, depth, pitch, format));
	}

	void load_bmp(const char* file) {
		_handle = std::move(make_resource(file));
	}

	void load_bmp_rw(SDL_RWops* src, int freesrc) {
		_handle = std::move(make_resource(src, freesrc));
	}

	bool palette(SDL_Palette *palette) noexcept { return (SDL_SetSurfacePalette(get(), palette) == 0); }

	bool must_lock() const noexcept { return SDL_MUSTLOCK(_handle); }

	bool lock() noexcept { return (SDL_LockSurface(get()) == 0); }

	void unlock() noexcept { SDL_UnlockSurface(get()); }

	bool save_bmp(const char* file) const noexcept { return (SDL_SaveBMP(get(), file) == 0); }

	bool save_bmp_rw(SDL_RWops *dst, int freedst) const noexcept { return (SDL_SaveBMP_RW(get(), dst, freedst) == 0); }

	bool rle(bool flag) noexcept { return (SDL_SetSurfaceRLE(get(), flag ? 1 : 0) == 0); }

	bool color_key(bool flag, Uint32 key = 0) noexcept { return (SDL_SetColorKey(get(), flag ? 1 : 0, key) == 0); }

	bool color_key(Uint32 *key) const noexcept { return (SDL_GetColorKey(get(), key) == 0); }

	Uint32 color_key() const noexcept { Uint32 result; SDL_GetColorKey(get(), &result); return result; }

	bool color_mod(Uint8 r, Uint8 g, Uint8 b) noexcept { return (SDL_SetSurfaceColorMod(get(), r, g, b) == 0); }

	bool color_mod(Uint8 *r, Uint8 *g, Uint8 *b) const noexcept { return (SDL_GetSurfaceColorMod(get(), r, g, b) == 0); }

	bool alpha_mod(Uint8 alpha) noexcept { return (SDL_SetSurfaceAlphaMod(get(), alpha) == 0); }

	bool alpha_mod(Uint8 *alpha) const noexcept { return (SDL_GetSurfaceAlphaMod(get(), alpha) == 0); }

	Uint8 alpha_mod() const noexcept { Uint8 result; alpha_mod(&result); return result; }

	bool blend_mode(SDL_BlendMode blendMode) noexcept { return (SDL_SetSurfaceBlendMode(get(), blendMode) == 0); }

	bool blend_mode(SDL_BlendMode *blendMode) const noexcept { return (SDL_GetSurfaceBlendMode(get(), blendMode) == 0); }

	SDL_BlendMode blend_mode() const noexcept { SDL_BlendMode result; blend_mode(&result); return result; }

	bool clip_rect(const SDL_Rect *rect) noexcept { return (SDL_SetClipRect(get(), rect) == SDL_TRUE); }

	bool clip_rect(const rect &rect) noexcept { return clip_rect(&rect); }

	void clip_rect(SDL_Rect *rect) const noexcept { SDL_GetClipRect(get(), rect); }

	void clip_rect(rect &rect) const noexcept { clip_rect(&rect); }

	SDL_Surface *convert(const SDL_PixelFormat * fmt, Uint32 flags) noexcept { return SDL_ConvertSurface(get(), fmt, flags); }

	SDL_Surface *convert_format(Uint32 pixel_format, Uint32 flags) noexcept {
		return SDL_ConvertSurfaceFormat(get(), pixel_format, flags);
	}

	bool fill_rect(const SDL_Rect *rect, Uint32 color) noexcept { return (SDL_FillRect(get(), rect, color) == 0); }

	bool fill_rect(const rect &rect, Uint32 color) noexcept { return (SDL_FillRect(get(), &rect, color) == 0); }

	bool fill_rect(const SDL_Rect *rects, int count, Uint32 color) noexcept { return (SDL_FillRects(get(), rects, count, color) == 0); }

	bool upper_blit(const SDL_Rect *srcrect, SDL_Surface *dst, SDL_Rect *dstrect) noexcept {
		return (SDL_UpperBlit(get(), srcrect, dst, dstrect) == 0);
	}

	bool lower_blit(SDL_Rect *srcrect, SDL_Surface *dst, SDL_Rect *dstrect) noexcept {
		return (SDL_LowerBlit(get(), srcrect, dst, dstrect) == 0);
	}

	bool soft_stretch(const SDL_Rect *srcrect, SDL_Surface *dst, const SDL_Rect *dstrect) noexcept {
		return (SDL_SoftStretch(get(), srcrect, dst, dstrect) == 0);
	}

	bool upper_blit_scaled(const SDL_Rect *srcrect, SDL_Surface *dst, SDL_Rect *dstrect) noexcept {
		return (SDL_UpperBlitScaled(get(), srcrect, dst, dstrect) == 0);
	}

	bool lower_blit_scaled(SDL_Rect *srcrect, SDL_Surface *dst, SDL_Rect *dstrect) noexcept {
		return (SDL_LowerBlitScaled(get(), srcrect, dst, dstrect) == 0);
	}

	bool blit(const SDL_Rect *srcrect, SDL_Surface *dst, SDL_Rect *dstrect) noexcept {
		return upper_blit(srcrect, dst, dstrect);
	}

	bool blit_scaled(const SDL_Rect *srcrect, SDL_Surface *dst, SDL_Rect *dstrect) noexcept {
		return upper_blit_scaled(srcrect, dst, dstrect);
	}

	void destroy() noexcept { _handle.reset(); }

public:
	Uint32 flags() const noexcept { return _handle->flags; }

	SDL_PixelFormat *format() const noexcept { return _handle->format; }

	int w() const noexcept { return _handle->w; }

	int h() const noexcept { return _handle->h; }

	point size() const noexcept { return { w(), h() }; }

	int pitch() const noexcept { return _handle->pitch; }

	void *pixels() const noexcept { return _handle->pixels; }

	void pixels(void *p) noexcept { _handle->pixels = p; }

	void *userdata() const noexcept { return _handle->userdata; }

	void userdata(void *p) noexcept { _handle->userdata = p; }

	int locked() const noexcept { return _handle->locked; }

	void *lock_data() const noexcept { return _handle->lock_data; }

	rect clip_rect() const noexcept { return _handle->clip_rect; }

	int refcount() const noexcept { return _handle->refcount; }

private:
	handle _handle;
};

} } // namespace sdl::video

#endif // SDL2_WRAPPER_VIDEO_SURFACE_HPP_

