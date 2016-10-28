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

#ifndef SDL2_WRAPPER_VIDEO_TEXTURE_HPP_
#define SDL2_WRAPPER_VIDEO_TEXTURE_HPP_

#include "../util.hpp"

namespace sdl { inline namespace video {

class texture {
public:
	using resource_t = SDL_Texture;

	using resource_ptr = resource_t *;

	using handle = std::unique_ptr<resource_t, decltype(&SDL_DestroyTexture)>;

	static handle make_resource(SDL_Renderer* renderer, Uint32 format, int access, int w, int h) {
		return sdl::detail::make_resource(SDL_CreateTexture, SDL_DestroyTexture, renderer, format, access, w, h);
	}

	static handle make_resource(SDL_Renderer* renderer, SDL_Surface* surface) {
		return sdl::detail::make_resource(SDL_CreateTextureFromSurface, SDL_DestroyTexture, renderer, surface);
	}

	explicit texture(SDL_Renderer* renderer, Uint32 format, int access, int w, int h)
		: _handle(make_resource(renderer, format, access, w, h)) {}

	explicit texture(SDL_Renderer* renderer, SDL_Surface* surface)
		: _handle(make_resource(renderer, surface)) {}

	resource_ptr get() const noexcept { return _handle.get(); }

	bool valid() const noexcept { return (get() != nullptr); }

	explicit operator bool() const { return valid(); }

	operator resource_ptr() const { return get(); }

	void create(SDL_Renderer* renderer, Uint32 format, int access, int w, int h) {
		_handle = std::move(make_resource(renderer, format, access, w, h));
	}

	void create(SDL_Renderer* renderer, SDL_Surface* surface) {
		_handle = std::move(make_resource(renderer, surface));
	}

	bool color_mod(Uint8 r, Uint8 g, Uint8 b) noexcept { return (SDL_SetTextureColorMod(get(), r, g, b) == 0); }

	bool color_mod(Uint8 *r, Uint8 *g, Uint8 *b) const noexcept { return (SDL_GetTextureColorMod(get(), r, g, b) == 0); }

	bool alpha_mod(Uint8 alpha) noexcept { return (SDL_SetTextureAlphaMod(get(), alpha) == 0); }

	bool alpha_mod(Uint8 *alpha) const noexcept { return (SDL_GetTextureAlphaMod(get(), alpha) == 0); }

	Uint8 alpha_mod() const noexcept { Uint8 result; alpha_mod(&result); return result; }

	bool blend_mode(SDL_BlendMode blendMode) noexcept { return (SDL_SetTextureBlendMode(get(), blendMode) == 0); }

	bool blend_mode(SDL_BlendMode *blendMode) const noexcept { return (SDL_GetTextureBlendMode(get(), blendMode) == 0); }

	SDL_BlendMode blend_mode() const noexcept { SDL_BlendMode result; blend_mode(&result); return result; }

	bool update(const SDL_Rect *rect, const void *pixels, int pitch) noexcept {
		return (SDL_UpdateTexture(get(), rect, pixels, pitch) == 0);
	}

	bool update(
		const SDL_Rect *rect,
		const Uint8 *Yplane, int Ypitch,
		const Uint8 *Uplane, int Upitch,
		const Uint8 *Vplane, int Vpitch) noexcept {
		return (SDL_UpdateYUVTexture(get(), rect, Yplane, Ypitch, Uplane, Upitch, Vplane, Vpitch) == 0);
	}

	bool lock(const SDL_Rect *rect, void **pixels, int *pitch) { return (SDL_LockTexture(get(), rect, pixels, pitch) == 0); }

	void unlock() { SDL_UnlockTexture(get()); }

	void destroy() noexcept { _handle.reset(); }

private:
	handle _handle;
};

} } // namespace sdl::video

#endif // SDL2_WRAPPER_VIDEO_TEXTURE_HPP_

