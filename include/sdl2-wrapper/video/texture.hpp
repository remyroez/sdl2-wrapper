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

namespace sdl { inline namespace video {

class texture final : public sdl::detail::resource<SDL_Texture, decltype(&SDL_DestroyTexture)> {
public:
	static decltype(auto) make_resource(SDL_Renderer* renderer, Uint32 format, int access, int w, int h) {
		return resource::make_resource(SDL_CreateTexture, SDL_DestroyTexture, renderer, format, access, w, h);
	}

	static decltype(auto) make_resource(SDL_Renderer* renderer, SDL_Surface* surface) {
		return resource::make_resource(SDL_CreateTextureFromSurface, SDL_DestroyTexture, renderer, surface);
	}

	explicit texture(SDL_Renderer* renderer, Uint32 format, int access, int w, int h)
		: resource(make_resource(renderer, format, access, w, h)) {}

	explicit texture(SDL_Renderer* renderer, SDL_Surface* surface)
		: resource(make_resource(renderer, surface)) {}

	void create(SDL_Renderer* renderer, Uint32 format, int access, int w, int h) {
		_handle_holder = make_resource(renderer, format, access, w, h);
	}

	void create(SDL_Renderer* renderer, SDL_Surface* surface) {
		_handle_holder = make_resource(renderer, surface);
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
};

} } // namespace sdl::video

#endif // SDL2_WRAPPER_VIDEO_TEXTURE_HPP_

