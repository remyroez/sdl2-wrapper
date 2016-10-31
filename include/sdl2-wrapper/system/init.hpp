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

#ifndef SDL2_WRAPPER_SYSTEM_INIT_HPP_
#define SDL2_WRAPPER_SYSTEM_INIT_HPP_

namespace sdl { inline namespace system {

bool init(Uint32 flags) {
	return (SDL_Init(flags) == 0);
}

void quit() { SDL_Quit(); }

bool init_subsystem(Uint32 flags) {
	return (SDL_InitSubSystem(flags) == 0);
}

void quit_subsystem(Uint32 flags) { SDL_QuitSubSystem(flags); }

bool was_init(Uint32 flags) {
	return (SDL_WasInit(flags) != 0);
}

} } // namespace sdl2::system

#endif // SDL2_WRAPPER_SYSTEM_INIT_HPP_

