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

namespace sdl { namespace video {

using surface_ptr = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>;

surface_ptr make_surface(Uint32 flags, int width, int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) {
	return sdl::detail::make_resource(SDL_CreateRGBSurface, SDL_FreeSurface, flags, width, height, depth, Rmask, Gmask, Bmask, Amask);
}

surface_ptr make_surface(void* pixels, int width, int height, int depth, int pitch, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) {
	return sdl::detail::make_resource(SDL_CreateRGBSurfaceFrom, SDL_FreeSurface, pixels, width, height, depth, pitch, Rmask, Gmask, Bmask, Amask);
}
#if 0
surface_ptr make_surface(Uint32 flags, int width, int height, int depth, Uint32 format) {
	return sdl::detail::make_resource(SDL_CreateRGBSurfaceWithFormat, SDL_FreeSurface, flags, width, height, depth, format);
}

surface_ptr make_surface(void* pixels, int width, int height, int depth, int pitch, Uint32 format) {
	return sdl::detail::make_resource(SDL_CreateRGBSurfaceWithFormatFrom, SDL_FreeSurface, pixels, width, height, depth, pitch, format);
}
#endif
surface_ptr make_surface(const char* file) {
	return surface_ptr(SDL_LoadBMP(file), SDL_FreeSurface);
}

surface_ptr make_surface(SDL_RWops* src, int freesrc) {
	return sdl::detail::make_resource(SDL_LoadBMP_RW, SDL_FreeSurface, src, freesrc);
}

} } // namespace sdl::video

#endif // SDL2_WRAPPER_VIDEO_SURFACE_HPP_

