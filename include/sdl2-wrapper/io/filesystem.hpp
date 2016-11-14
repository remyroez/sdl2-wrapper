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

#ifndef SDL2_WRAPPER_IO_FILESYSTEM_HPP_
#define SDL2_WRAPPER_IO_FILESYSTEM_HPP_

#include <memory>
#include <string>

namespace sdl { inline namespace io {

struct filesystem final {
	using path = std::unique_ptr<char, decltype(&SDL_free)>;

	static path base_path() noexcept { return path(SDL_GetBasePath(), SDL_free); }

	static path pref_path(std::string org, std::string app) noexcept { return path(SDL_GetPrefPath(org.c_str(), app.c_str()), SDL_free); }
};

} } // namespace sdl::io

#endif // SDL2_WRAPPER_IO_FILESYSTEM_HPP_

