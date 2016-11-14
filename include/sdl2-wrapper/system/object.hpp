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

#ifndef SDL2_WRAPPER_SYSTEM_OBJECT_HPP_
#define SDL2_WRAPPER_SYSTEM_OBJECT_HPP_

#include <string>

namespace sdl { inline namespace system {

class object : public sdl::detail::resource<void, decltype(&SDL_UnloadObject)> {
public:
	static inline decltype(auto) make_resource(std::string file) {
		return resource::make_resource(SDL_LoadObject, SDL_UnloadObject, file.c_str());
	}

public:
	using resource::resource;
	using resource::operator=;

	object() = default;

	object(std::string file) : resource(make_resource(file)) {}

	template <typename Function>
	Function load_function(const char* name) const noexcept { return static_cast<Function>(SDL_LoadFunction(get(), name)); }
};

} } // namespace sdl::system

#endif // SDL2_WRAPPER_SYSTEM_OBJECT_HPP_

