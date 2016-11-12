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

#ifndef SDL2_WRAPPER_EVENT_MOUSE_CURSOR_HPP_
#define SDL2_WRAPPER_EVENT_MOUSE_CURSOR_HPP_

namespace sdl { inline namespace event {

class mouse_cursor : public sdl::detail::resource<SDL_Cursor, decltype(&SDL_FreeCursor)> {
public:
	enum class system_mouse_cursor_type : std::underlying_type_t<SDL_SystemCursor> {
		arrow = SDL_SYSTEM_CURSOR_ARROW,     /**< Arrow */
		i_beam = SDL_SYSTEM_CURSOR_IBEAM,     /**< I-beam */
		wait = SDL_SYSTEM_CURSOR_WAIT,      /**< Wait */
		crosshair = SDL_SYSTEM_CURSOR_CROSSHAIR, /**< Crosshair */
		wait_allow = SDL_SYSTEM_CURSOR_WAITARROW, /**< Small wait cursor (or Wait if not available) */
		size_nwse = SDL_SYSTEM_CURSOR_SIZENWSE,  /**< Double arrow pointing northwest and southeast */
		size_nesw = SDL_SYSTEM_CURSOR_SIZENESW,  /**< Double arrow pointing northeast and southwest */
		size_we = SDL_SYSTEM_CURSOR_SIZEWE,    /**< Double arrow pointing west and east */
		size_ns = SDL_SYSTEM_CURSOR_SIZENS,    /**< Double arrow pointing north and south */
		size_all = SDL_SYSTEM_CURSOR_SIZEALL,   /**< Four pointed arrow pointing north, south, east, and west */
		no = SDL_SYSTEM_CURSOR_NO,        /**< Slashed circle or crossbones */
		hand = SDL_SYSTEM_CURSOR_HAND,      /**< Hand */
	};

	static inline void set_current(SDL_Cursor *cursor) noexcept { SDL_SetCursor(cursor); }

	static inline void set_default() noexcept { set_current(get_default()); }

	static inline SDL_Cursor *get_current() noexcept { return SDL_GetCursor(); }

	static inline SDL_Cursor *get_default() noexcept { return SDL_GetDefaultCursor(); }

	static inline bool show(bool b) noexcept { return (SDL_ShowCursor(b ? SDL_ENABLE : SDL_DISABLE) == SDL_ENABLE); }

	static inline bool show() noexcept { return (SDL_ShowCursor(-1) == SDL_ENABLE); }

	static inline decltype(auto) make_resource(const Uint8 *data, const Uint8 *mask, int w, int h, int hot_x, int hot_y) {
		return resource::make_resource(SDL_CreateCursor, SDL_FreeCursor, data, mask, w, h, hot_x, hot_y);
	}

	static inline decltype(auto) make_resource(SDL_Surface *surface, int hot_x, int hot_y) {
		return resource::make_resource(SDL_CreateColorCursor, SDL_FreeCursor, surface, hot_x, hot_y);
	}

	static inline decltype(auto) make_resource(system_mouse_cursor_type type) {
		return resource::make_resource(SDL_CreateSystemCursor, SDL_FreeCursor, static_cast<SDL_SystemCursor>(type));
	}

public:
	using resource::resource;
	using resource::operator=;

	mouse_cursor() = default;

	mouse_cursor(const Uint8 *data, const Uint8 *mask, int w, int h, int hot_x, int hot_y)
		: resource(make_resource(data, mask, w, h, hot_x, hot_y)) {}

	mouse_cursor(SDL_Surface *surface, int hot_x, int hot_y)
		: resource(make_resource(surface, hot_x, hot_y)) {}

	mouse_cursor(system_mouse_cursor_type type)
		: resource(make_resource(type)) {}

	void create(const Uint8 *data, const Uint8 *mask, int w, int h, int hot_x, int hot_y) {
		reset(make_resource(data, mask, w, h, hot_x, hot_y));
	}

	void create(SDL_Surface *surface, int hot_x, int hot_y) {
		reset(make_resource(surface, hot_x, hot_y));
	}

	void create(system_mouse_cursor_type type) {
		reset(make_resource(type));
	}

	void set() noexcept { set_current(get()); }
};

} } // namespace sdl::event

#endif // SDL2_WRAPPER_EVENT_MOUSE_CURSOR_HPP_

