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

#ifndef SDL2_WRAPPER_EVENT_MOUSE_HPP_
#define SDL2_WRAPPER_EVENT_MOUSE_HPP_

namespace sdl { inline namespace event {

struct mouse {
	enum class button : Uint32 {
		left = SDL_BUTTON_LEFT,
		middle = SDL_BUTTON_MIDDLE,
		right = SDL_BUTTON_RIGHT,
		x1 = SDL_BUTTON_X1,
		x2 = SDL_BUTTON_X2,
	};

	static bool is_pressed(button b) { return ((current_state() & SDL_BUTTON(static_cast<Uint32>(b))) != 0); }

	static SDL_Window *focus() noexcept { return SDL_GetMouseFocus(); }

	static Uint32 current_state(int *x = nullptr, int *y = nullptr) noexcept { return SDL_GetMouseState(x, y); }

	static Uint32 global_state(int *x = nullptr, int *y = nullptr) noexcept { return SDL_GetGlobalMouseState(x, y); }

	static Uint32 relative_state(int *x = nullptr, int *y = nullptr) noexcept { return SDL_GetRelativeMouseState(x, y); }

	static void warp_in_window(int x, int y, SDL_Window *window = nullptr) noexcept { SDL_WarpMouseInWindow(window, x, y); }

	static void warp(int x, int y) noexcept { SDL_WarpMouseGlobal(x, y); }

	static bool relative(bool b) noexcept { return (SDL_SetRelativeMouseMode(b ? SDL_TRUE : SDL_FALSE) == 0); }

	static bool relative() noexcept { return (SDL_GetRelativeMouseMode() == SDL_TRUE); }

	static bool capture(bool b) noexcept { return (SDL_CaptureMouse(b ? SDL_TRUE : SDL_FALSE) == 0); }
};

} } // namespace sdl::event

#endif // SDL2_WRAPPER_EVENT_MOUSE_HPP_

