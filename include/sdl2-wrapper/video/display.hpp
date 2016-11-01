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

#ifndef SDL2_WRAPPER_VIDEO_DISPLAY_HPP_
#define SDL2_WRAPPER_VIDEO_DISPLAY_HPP_

#include <string>

namespace sdl { inline namespace video {

class display {
public:
	display() : _index(0) {}

	display(int index) : _index(index) {}

	display(const display &other) : _index(other.index()) {}

	explicit operator bool() const noexcept { return valid(); }

	int index() const noexcept { return _index; }

	void index(int i) noexcept { _index = i; }

	bool valid() const noexcept { return (index() >= 0); }

	std::string name() const noexcept { return SDL_GetDisplayName(index()); }

	bool bounds(SDL_Rect *rect) const noexcept { return (SDL_GetDisplayBounds(index(), rect) == 0); }

	rect bounds() const noexcept { rect result; bounds(&result); return result; }

	bool dpi(float *ddpi, float *hdpi, float *vdpi) const noexcept {
		return (SDL_GetDisplayDPI(index(), ddpi, hdpi, vdpi) == 0);
	}

	bool usable_bounds(SDL_Rect *rect) const noexcept { return (SDL_GetDisplayUsableBounds(index(), rect) == 0); }

	rect usable_bounds() const noexcept { rect result; usable_bounds(&result); return result; }

	int num_modes() const noexcept { return SDL_GetNumDisplayModes(index()); }

	bool mode(int modeIndex, display_mode *mode) const noexcept { return (SDL_GetDisplayMode(index(), modeIndex, mode) == 0); }

	display_mode mode(int modeIndex) const noexcept { display_mode result; mode(modeIndex, &result); return result; }

	bool desktop_mode(display_mode *mode) const noexcept { return (SDL_GetDesktopDisplayMode(index(), mode) == 0); }

	display_mode desktop_mode() const noexcept { display_mode result; desktop_mode(&result); return result; }

	bool current_mode(display_mode *mode) const noexcept { return (SDL_GetCurrentDisplayMode(index(), mode) == 0); }

	display_mode current_mode() const noexcept { display_mode result; current_mode(&result); return result; }

	bool closest_mode(const display_mode *desired, display_mode *closest) const noexcept {
		return (SDL_GetClosestDisplayMode(index(), desired, closest) != nullptr);
	}

	display_mode closest_mode(const display_mode desired) const noexcept {
		display_mode closest;
		return closest_mode(&desired, &closest) ? closest : display_mode{ 0U, 0, 0, 0, nullptr};
	}

	display_mode closest_mode(int w, int h) const noexcept {
		display_mode desired(w, h);
		display_mode closest;
		return closest_mode(&desired, &closest) ? closest : display_mode{ 0U, 0, 0, 0, nullptr };
	}

private:
	int _index;
};

} } // namespace sdl::video

#endif // SDL2_WRAPPER_VIDEO_DISPLAY_HPP_

