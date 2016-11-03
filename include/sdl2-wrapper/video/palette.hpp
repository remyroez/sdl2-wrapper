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

#ifndef SDL2_WRAPPER_VIDEO_PALETTE_HPP_
#define SDL2_WRAPPER_VIDEO_PALETTE_HPP_

#include <vector>

namespace sdl { inline namespace video {

class palette final : public sdl::detail::resource<SDL_Palette, decltype(&SDL_FreePalette)> {
public:
	static decltype(auto) make_resource(int ncolors) {
		return base::make_resource(SDL_AllocPalette, SDL_FreePalette, ncolors);
	}

public:
	palette() = default;

	explicit palette(int ncolors) : base(make_resource(ncolors)) {}

	auto ncolors() const noexcept { return (valid() ? get()->ncolors : 0); }

	std::vector<color> colors() const noexcept {
		std::vector<color> list;

		if (valid()) {
			auto colors = get()->colors;
			for (auto i = 0; i < ncolors(); ++i) {
				list.emplace_back(colors[i]);
			}
		}

		return list;
	}

	auto version() const noexcept { return (valid() ? get()->version : 0); }

	void create(int ncolors) noexcept {
		_handle_holder = make_resource(ncolors);
	}

	bool colors(const SDL_Color *colors, int firstcolor, int ncolors) noexcept {
		return (SDL_SetPaletteColors(get(), colors, firstcolor, ncolors) == 0);
	}

	template <typename T>
	bool colors(const T &colors, int firstcolor = 0, int ncolors = -1) noexcept {
		return colors(colors.data(), (ncolors <= 0) ? colors.size() : ncolors, firstcolor);
	}
};

} } // namespace sdl::video

#endif // SDL2_WRAPPER_VIDEO_PALETTE_HPP_

