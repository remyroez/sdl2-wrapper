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

#ifndef SDL2_WRAPPER_CORE_ASSERT_HPP_
#define SDL2_WRAPPER_CORE_ASSERT_HPP_

namespace sdl { inline namespace core {

struct assert final {
	enum class state : std::underlying_type_t<SDL_AssertState> {
		retry = SDL_ASSERTION_RETRY, 
		breaks = SDL_ASSERTION_BREAK, 
		abort = SDL_ASSERTION_ABORT, 
		ignore = SDL_ASSERTION_IGNORE,
		always_ignore = SDL_ASSERTION_ALWAYS_IGNORE,
	};

	using data = SDL_AssertData;
	using assertion_handler = SDL_AssertionHandler;

	static void handler(assertion_handler handler, void *userdata) noexcept { SDL_SetAssertionHandler(handler, userdata); }

	static assertion_handler handler(void **puserdata) noexcept { return SDL_GetAssertionHandler(puserdata); }

	static assertion_handler handler() noexcept { return SDL_GetDefaultAssertionHandler(); }

	static const data *report() noexcept { return SDL_GetAssertionReport(); }

	static void reset_report() noexcept { return SDL_ResetAssertionReport(); }
};

} } // namespace sdl::core

#endif // SDL2_WRAPPER_CORE_ASSERT_HPP_

