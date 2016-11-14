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

#ifndef SDL2_WRAPPER_TIMER_TIMER_HPP_
#define SDL2_WRAPPER_TIMER_TIMER_HPP_

namespace sdl { namespace timer {

using timer_id = SDL_TimerID;

using timer_callback = SDL_TimerCallback;

Uint32 ticks() noexcept { return SDL_GetTicks(); }

template <typename T, typename U>
inline bool ticks_passed(T a, T b) noexcept { return SDL_TICKS_PASSED(a, b); }

Uint64 peformance_counter() noexcept { return SDL_GetPerformanceCounter(); }

Uint64 peformance_frequency() noexcept { return SDL_GetPerformanceFrequency(); }

void delay(Uint32 ms) noexcept { SDL_Delay(ms); }

timer_id add_timer(Uint32 interval, timer_callback callback, void *param) noexcept {
	return SDL_AddTimer(interval, callback, param);
}

bool remove_timer(timer_id id) noexcept { return (SDL_RemoveTimer(id) == SDL_TRUE); }

} } // namespace sdl::timer

#endif // SDL2_WRAPPER_TIMER_TIMER_HPP_

