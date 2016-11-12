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

#ifndef SDL2_WRAPPER_EVENT_KEYBOARD_HPP_
#define SDL2_WRAPPER_EVENT_KEYBOARD_HPP_

#include <string>

namespace sdl { inline namespace event {

struct keyboard {
	static SDL_Window *focus() noexcept { return SDL_GetKeyboardFocus(); }

	static const Uint8 *current_state(int *numkeys = nullptr) noexcept { return SDL_GetKeyboardState(numkeys); }

	static bool is_pressed(scancode code) noexcept { return (current_state()[static_cast<std::size_t>(code)] != 0); }

	static bool is_pressed(keycode code) noexcept { return is_pressed(to_scancode(code)); }

	static keymod modifier_state() noexcept { return static_cast<keymod>(SDL_GetModState()); }

	static void modifier_state(keymod modstate) noexcept { SDL_SetModState(static_cast<SDL_Keymod>(modstate)); }

	static bool is_modifier_pressed(keymod mod) noexcept { return ((static_cast<Uint32>(modifier_state()) & (static_cast<Uint32>(mod))) != 0); }

	static keycode to_keycode(scancode code) noexcept { return static_cast<keycode>(SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(code))); }

	static keycode to_keycode(std::string name) noexcept { return static_cast<keycode>(SDL_GetKeyFromName(name.c_str())); }

	static std::string keycode_name(keycode code) noexcept { return SDL_GetKeyName(static_cast<SDL_Keycode>(code)); }

	static scancode to_scancode(keycode code) noexcept { return static_cast<scancode>(SDL_GetScancodeFromKey(static_cast<SDL_Keycode>(code))); }
	
	static scancode to_scancode(std::string name) noexcept { return static_cast<scancode>(SDL_GetScancodeFromName(name.c_str())); }

	static std::string scancode_name(scancode code) noexcept { return SDL_GetScancodeName(static_cast<SDL_Scancode>(code)); }

	static void start_text_input() noexcept { SDL_StartTextInput(); }

	static void stop_text_input() noexcept { SDL_StopTextInput(); }

	static bool is_text_input_active() noexcept { return (SDL_IsTextInputActive() == SDL_TRUE); }

	static void text_input_rect(SDL_Rect *rect) noexcept { SDL_SetTextInputRect(rect); }

	static bool has_screen_keyboard() noexcept { return (SDL_HasScreenKeyboardSupport() == SDL_TRUE); }

	static bool is_screen_keyboard_shown(SDL_Window *window) noexcept { return (SDL_IsScreenKeyboardShown(window) == SDL_TRUE); }
};

} } // namespace sdl::event

#endif // SDL2_WRAPPER_EVENT_KEYBOARD_HPP_

