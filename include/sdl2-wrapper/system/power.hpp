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

#ifndef SDL2_WRAPPER_SYSTEM_POWER_HPP_
#define SDL2_WRAPPER_SYSTEM_POWER_HPP_

namespace sdl { inline namespace system {

struct power {
	enum class power_state : int {
		unknown = SDL_POWERSTATE_UNKNOWN,
		on_battery = SDL_POWERSTATE_ON_BATTERY,
		no_battery = SDL_POWERSTATE_NO_BATTERY,
		charging = SDL_POWERSTATE_CHARGING,
		charged = SDL_POWERSTATE_CHARGED
	};

	static inline SDL_PowerState get_power_info(int *secs, int *pct) noexcept { return SDL_GetPowerInfo(secs, pct); }

	static inline power get() noexcept {
		power result; result.state = static_cast<power_state>(get_power_info(&result.seconds, &result.battery)); return result;
	}

	power_state state;
	int seconds;
	int battery;
};

} } // namespace sdl2::system

#endif // SDL2_WRAPPER_SYSTEM_POWER_HPP_

