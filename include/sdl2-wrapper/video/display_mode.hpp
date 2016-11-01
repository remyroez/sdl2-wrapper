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

#ifndef SDL2_WRAPPER_VIDEO_DISPLAY_MODE_HPP_
#define SDL2_WRAPPER_VIDEO_DISPLAY_MODE_HPP_

namespace sdl { inline namespace video {

class display_mode : public SDL_DisplayMode {
public:
	using SDL_DisplayMode::SDL_DisplayMode;

	display_mode() : SDL_DisplayMode{ 0U, 0, 0, 0, nullptr } {}

	display_mode(Uint32 format, int w, int h, int refresh_rate, void *driverdata)
		: SDL_DisplayMode{ format, w, h, refresh_rate, driverdata } {}

	display_mode(int w, int h)
		: SDL_DisplayMode{ 0U, w, h, 0, nullptr } {}
};

} } // namespace sdl::video

#endif // SDL2_WRAPPER_VIDEO_DISPLAY_MODE_HPP_

