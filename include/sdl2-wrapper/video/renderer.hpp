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

#ifndef SDL2_WRAPPER_VIDEO_RENDERER_HPP_
#define SDL2_WRAPPER_VIDEO_RENDERER_HPP_

#include "../util.hpp"

namespace sdl { namespace video {

using renderer_ptr = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

renderer_ptr make_renderer(SDL_Window* window, int index, Uint32 flags) {
	return sdl::detail::make_resource(SDL_CreateRenderer, SDL_DestroyRenderer, window, index, flags);
}

renderer_ptr make_renderer(SDL_Surface* surface) {
	return sdl::detail::make_resource(SDL_CreateSoftwareRenderer, SDL_DestroyRenderer, surface);
}

} } // namespace sdl::video

#endif // SDL2_WRAPPER_VIDEO_RENDERER_HPP_

