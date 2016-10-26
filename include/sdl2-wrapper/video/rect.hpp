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

#ifndef SDL2_WRAPPER_VIDEO_RECT_HPP_
#define SDL2_WRAPPER_VIDEO_RECT_HPP_

namespace sdl { namespace video {

struct rect : public SDL_Rect
{
	rect() : SDL_Rect{ 0, 0, 0, 0 } {}
	rect(int x, int y, int w, int h) : SDL_Rect{ x, y, w, h } {}
	rect(const SDL_Point &begin, const SDL_Point &end) : SDL_Rect{ begin.x, begin.y, end.x - begin.x, end.y - begin.y } {}

	auto left() const { return x; }
	auto right() const { return x + w; }
	auto top() const { return y; }
	auto bottom() const { return y + h; }

	auto begin() const { return SDL_Point{ left(), top() }; }
	auto end() const { return SDL_Point{ right(), bottom() }; }
};

} } // namespace sdl::video

#endif // SDL2_WRAPPER_VIDEO_RECT_HPP_

