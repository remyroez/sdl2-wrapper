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

#ifndef SDL2_WRAPPER_VIDEO_HPP_
#define SDL2_WRAPPER_VIDEO_HPP_

// SDL_rect.h
#include "video/point.hpp"
#include "video/rect.hpp"

// SDL_pixel.h
#include "video/color.hpp"
#include "video/palette.hpp"
#include "video/pixel_format.hpp"

// SDL_surface.h
#include "video/surface.hpp"

// SDL_render.h
#include "video/renderer.hpp"
#include "video/texture.hpp"

// SDL_video.h
#include "video/video_driver.hpp"
#include "video/display_mode.hpp"
#include "video/display.hpp"
#include "video/screen_saver.hpp"
#include "video/window.hpp"
#include "video/message_box.hpp"

#endif // SDL2_WRAPPER_VIDEO_HPP_

