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

#ifndef SDL2_WRAPPER_VIDEO_WINDOW_HPP_
#define SDL2_WRAPPER_VIDEO_WINDOW_HPP_

#include "point.hpp"

namespace sdl { inline namespace video {

class window final : public sdl::detail::resource<SDL_Window, decltype(&SDL_DestroyWindow)>
{
public:
	static inline decltype(auto) make_resource(
		const char *title,
		int x,
		int y,
		int w,
		int h,
		Uint32 flags
	) {
		return base::make_resource(
			SDL_CreateWindow,
			SDL_DestroyWindow,
			title,
			x,
			y,
			w,
			h,
			flags
		);
	}

	static inline decltype(auto) make_resource(const void* data) {
		return base::make_resource(SDL_CreateWindowFrom, SDL_DestroyWindow, data);
	}

public:
	using base::base;
	using base::operator=;

	window() = default;

	explicit window(const char *title, int x, int y, int w, int h, Uint32 flags)
		: base(make_resource(title, x, y, w, h, flags)) {}

	explicit window(const void* data)
		: base(make_resource(data)) {}

	void create(const char *title, int x, int y, int w, int h, Uint32 flags) {
		_handle_holder = make_resource(title, x, y, w, h, flags);
	}

	void create_from(const void* data) {
		_handle_holder = make_resource(data);
	}

	auto display_index() const noexcept { return SDL_GetWindowDisplayIndex(get()); }

	void display_mode(const display_mode mode) noexcept { SDL_SetWindowDisplayMode(get(), &mode); }

	auto display_mode() const noexcept { sdl::display_mode mode; SDL_GetWindowDisplayMode(get(), &mode); return mode; }

	auto pixel_format() const noexcept { return SDL_GetWindowPixelFormat(get()); }

	auto id() const noexcept { return SDL_GetWindowID(get()); }

	auto flags() const noexcept { return SDL_GetWindowFlags(get()); }

	void title(const char *title) { SDL_SetWindowTitle(get(), title); }

	auto title() const noexcept { return SDL_GetWindowTitle(get()); }

	void icon(SDL_Surface *icon) { SDL_SetWindowIcon(get(), icon); }

	auto userdata(const char *name, void *data) { return SDL_SetWindowData(get(), name, data); }

	auto userdata(const char *name) { return SDL_GetWindowData(get(), name); }

	void position(int x, int y) { SDL_SetWindowPosition(get(), x, y); }

	void position(const sdl::video::point &point) { SDL_SetWindowPosition(get(), point.x, point.y); }

	auto position() const noexcept { sdl::video::point result; SDL_GetWindowPosition(get(), &result.x, &result.y); return result; }

	void size(int w, int h) noexcept { SDL_SetWindowSize(get(), w, h); }

	auto size() const noexcept { sdl::video::point result; SDL_GetWindowSize(get(), &result.x, &result.y); return result; }

	void borders_size(int *top, int *left, int *bottom, int *right) const { SDL_GetWindowBordersSize(get(), top, left, bottom, right); }

	void minimum_size(int w, int h) noexcept { SDL_SetWindowMinimumSize(get(), w, h); }

	auto minimum_size() const noexcept { sdl::video::point result; SDL_GetWindowMinimumSize(get(), &result.x, &result.y); return result; }

	void maximum_size(int w, int h) noexcept { SDL_SetWindowMaximumSize(get(), w, h); }

	auto maximum_size() const noexcept { sdl::video::point result; SDL_GetWindowMaximumSize(get(), &result.x, &result.y); return result; }

	void bordered(bool b) noexcept { SDL_SetWindowBordered(get(), b ? SDL_TRUE : SDL_FALSE); }

	void resizable(bool b) noexcept { SDL_SetWindowResizable(get(), b ? SDL_TRUE : SDL_FALSE); }

	void show() noexcept { SDL_ShowWindow(get()); }

	void hide() noexcept { SDL_HideWindow(get()); }

	void raise() noexcept { SDL_RaiseWindow(get()); }

	void maximize() noexcept { SDL_MaximizeWindow(get()); }

	void minimize() noexcept { SDL_MinimizeWindow(get()); }

	void restore() noexcept { SDL_RestoreWindow(get()); }

	bool fullscreen(Uint32 flags = SDL_WINDOW_FULLSCREEN) noexcept { return (SDL_SetWindowFullscreen(get(), flags) == 0); }

	bool fullscreen_desktop() noexcept { return fullscreen(SDL_WINDOW_FULLSCREEN_DESKTOP); }

	bool windowed() noexcept { return fullscreen(0); }

	auto surface() const noexcept { return SDL_GetWindowSurface(get()); }

	bool update_surface() noexcept { return (SDL_UpdateWindowSurface(get()) == 0); }

	bool update_surface_rects(const rect *rects, int numrects) noexcept { return (SDL_UpdateWindowSurfaceRects(get(), rects, numrects) == 0); }

	void grab(bool b) noexcept { SDL_SetWindowGrab(get(), b ? SDL_TRUE : SDL_FALSE); }

	bool grab() const noexcept { return (SDL_GetWindowGrab(get()) == SDL_TRUE); }

	bool brightness(float f) noexcept { return (SDL_SetWindowBrightness(get(), f) == 0); }

	auto brightness() const noexcept { return SDL_GetWindowBrightness(get()); }

	bool opacity(float f) noexcept { return (SDL_SetWindowOpacity(get(), f) == 0); }

	auto opacity() const noexcept { float f; SDL_GetWindowOpacity(get(), &f); return f; }

	bool modal_for(SDL_Window *parent) noexcept { SDL_SetWindowModalFor(get(), parent); }

	bool input_focus() noexcept { return (SDL_SetWindowInputFocus(get()) == 0); }

	bool gamma_ramp(const Uint16 *red, const Uint16 *green, const Uint16 *blue) const noexcept { return (SDL_SetWindowGammaRamp(get(), red, green, blue) == 0); }

	bool gamma_ramp(Uint16 *red, Uint16 *green, Uint16 *blue) noexcept { return (SDL_GetWindowGammaRamp(get(), red, green, blue) == 0); }

	bool hit_test(SDL_HitTest callback, void *callback_data) noexcept { SDL_SetWindowHitTest(get(), callback, callback_data); }
};

} } // namespace sdl::video

#endif // SDL2_WRAPPER_VIDEO_WINDOW_HPP_

