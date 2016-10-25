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

namespace sdl { namespace video {

using texture_ptr = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;

texture_ptr make_texture(SDL_Renderer* renderer, Uint32 format, int access, int w, int h) {
	return sdl::detail::make_resource(SDL_CreateTexture, SDL_DestroyTexture, renderer, format, access, w, h);
}

texture_ptr make_texture(SDL_Renderer* renderer, SDL_Surface* surface) {
	return sdl::detail::make_resource(SDL_CreateTextureFromSurface, SDL_DestroyTexture, renderer, surface);
}

} } // namespace sdl::video

#endif // SDL2_WRAPPER_VIDEO_TEXTURE_HPP_

