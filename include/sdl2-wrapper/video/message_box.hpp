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

#ifndef SDL2_WRAPPER_VIDEO_MESSAGE_BOX_HPP_
#define SDL2_WRAPPER_VIDEO_MESSAGE_BOX_HPP_

#include <string>
#include <vector>

namespace sdl { inline namespace video {

class message_box final {
public:
	enum class flag : Uint32 {
		error = SDL_MESSAGEBOX_ERROR,
		warning = SDL_MESSAGEBOX_WARNING,
		information = SDL_MESSAGEBOX_INFORMATION
	};

	enum class position : std::size_t {
		background = SDL_MESSAGEBOX_COLOR_BACKGROUND,
		text = SDL_MESSAGEBOX_COLOR_TEXT,
		border = SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
		button_background = SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
		button_selected = SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
		max = SDL_MESSAGEBOX_COLOR_MAX
	};

	enum class button_flag : Uint32 {
		none = 0,
		return_default = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
		escape_default = SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,
	};

	static bool simple(const char *title, const char *message, flag flags = flag::information, SDL_Window *window = nullptr) noexcept {
		return (SDL_ShowSimpleMessageBox(static_cast<std::underlying_type_t<flag>>(flags), title, message, window) == 0);
	}

	message_box() :
		_data{ 0U, nullptr, nullptr, nullptr, 0, nullptr, nullptr } {
		SDL_zero(_color_scheme);
	}

	message_box(const char *title, const char *message, flag flags = flag::information, SDL_Window *window = nullptr) :
		_data{ static_cast<std::underlying_type_t<flag>>(flags), window, title, message, 0, nullptr, nullptr } {
		SDL_zero(_color_scheme);
	}

	void flags(flag flags) noexcept { _data.flags = static_cast<std::underlying_type_t<flag>>(flags); }

	void window(SDL_Window *window) noexcept { _data.window = window; }

	void title(const char *title) noexcept { _data.title = title; }

	void message(const char *message) noexcept { _data.message = message; }

	void use_color_scheme(bool b) noexcept { _use_color_scheme = b; }

	void color(position pos, SDL_MessageBoxColor color) noexcept {
		_color_scheme.colors[static_cast<std::underlying_type_t<position>>(pos)] = color;
	}

	void push_button(int id, const char *text, button_flag flags = button_flag::none) {
		_buttons.push_back({ static_cast<std::underlying_type_t<button_flag>>(flags), id, text });
	}

	void clear_buttons() { _buttons.clear(); }

	int show() noexcept {
		_data.numbuttons = _buttons.size();
		_data.buttons = _buttons.data();
		_data.colorScheme = _use_color_scheme ? &_color_scheme : nullptr;

		int button_id;
		int result = SDL_ShowMessageBox(&_data, &button_id);
		if (result != 0) {
			button_id = result;
		}

		return button_id;
	}

private:
	SDL_MessageBoxData _data;
	SDL_MessageBoxColorScheme _color_scheme;
	std::vector<SDL_MessageBoxButtonData> _buttons;
	bool _use_color_scheme = false;
};

} } // namespace sdl::video

#endif // SDL2_WRAPPER_VIDEO_MESSAGE_BOX_HPP_
