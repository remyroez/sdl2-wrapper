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

#ifndef SDL2_WRAPPER_EVENT_JOYSTICK_HPP_
#define SDL2_WRAPPER_EVENT_JOYSTICK_HPP_

#include <string>

namespace sdl { inline namespace event {

class joystick final : public sdl::detail::resource<SDL_Joystick, decltype(&SDL_JoystickClose)> {
public:
	using id = SDL_JoystickID;
	using guid = SDL_JoystickGUID;

	static inline decltype(auto) make_resource(int device_index) {
		return resource::make_resource(SDL_JoystickOpen, SDL_JoystickClose, device_index);
	}

	static inline decltype(auto) make_resource_from_id(id joyid) {
		return resource::make_resource(SDL_JoystickFromInstanceID, [](auto *) {}, joyid);
	}

	enum class power_level : std::underlying_type_t<SDL_JoystickPowerLevel> {
		unknown = SDL_JOYSTICK_POWER_UNKNOWN,
		empty = SDL_JOYSTICK_POWER_EMPTY,
		low = SDL_JOYSTICK_POWER_LOW,
		medium = SDL_JOYSTICK_POWER_MEDIUM,
		full = SDL_JOYSTICK_POWER_FULL,
		wired = SDL_JOYSTICK_POWER_WIRED,
		max = SDL_JOYSTICK_POWER_MAX
	};

	enum class hat_state : Uint8 {
		centered = SDL_HAT_CENTERED,
		up = SDL_HAT_UP,
		right = SDL_HAT_RIGHT,
		down = SDL_HAT_DOWN,
		left = SDL_HAT_LEFT,
		right_up = SDL_HAT_RIGHTUP,
		right_down = SDL_HAT_RIGHTDOWN,
		left_up = SDL_HAT_LEFTUP,
		left_down = SDL_HAT_LEFTDOWN,
	};

	static joystick from_instance_id(id joyid) { return joystick(make_resource_from_id(joyid)); }

	static int count() noexcept { return SDL_NumJoysticks(); }

	static std::string name(int device_index) noexcept { return SDL_JoystickNameForIndex(device_index); }

	static guid device_guid(int device_index) noexcept { return SDL_JoystickGetDeviceGUID(device_index); }

	static void guid_to_string(SDL_JoystickGUID guid, char *pszGUID, int cbGUID) noexcept {
		SDL_JoystickGetGUIDString(guid, pszGUID, cbGUID);
	}

	static std::string guid_to_string(SDL_JoystickGUID guid) noexcept {
		char pszGUID[33];
		guid_to_string(guid, pszGUID, sizeof(pszGUID));
		return pszGUID;
	}

	static guid guid_from_string(std::string name) noexcept { return SDL_JoystickGetGUIDFromString(name.c_str()); }

	static void update() noexcept { return SDL_JoystickUpdate(); }

	static event_state state(event_state state = event_state::query) noexcept {
		return static_cast<event_state>(SDL_JoystickEventState(static_cast<int>(state)));
	}

public:
	using resource::resource;
	using resource::operator=;

	joystick() = default;

	explicit joystick(int device_index) : resource(make_resource(device_index)) {}

	void create(int device_index) { reset(make_resource(device_index)); }

	std::string name() const noexcept { return SDL_JoystickName(get()); }

	guid device_guid() const noexcept { return SDL_JoystickGetGUID(get()); }

	bool attached() const noexcept { return (SDL_JoystickGetAttached(get()) == SDL_TRUE); }

	id instance_id() const noexcept { return SDL_JoystickInstanceID(get()); }

	int axes() const noexcept { return SDL_JoystickNumAxes(get()); }

	int balls() const noexcept { return SDL_JoystickNumBalls(get()); }

	int hats() const noexcept { return SDL_JoystickNumHats(get()); }

	int buttons() const noexcept { return SDL_JoystickNumButtons(get()); }

	Sint16 axis(int axis) const noexcept { return SDL_JoystickGetAxis(get(), axis); }

	hat_state hat(int hat) const noexcept { return static_cast<hat_state>(SDL_JoystickGetHat(get(), hat)); }

	bool ball(int ball, int *dx, int *dy) const noexcept { return (SDL_JoystickGetBall(get(), ball, dx, dy) == 0); }

	Uint8 button(int button) const noexcept { return SDL_JoystickGetButton(get(), button); }

	power_level current_power_level() const noexcept { return static_cast<power_level>(SDL_JoystickCurrentPowerLevel(get())); }
};

} } // namespace sdl::event

#endif // SDL2_WRAPPER_EVENT_JOYSTICK_HPP_

