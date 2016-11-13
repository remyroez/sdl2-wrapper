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

#ifndef SDL2_WRAPPER_EVENT_GAME_CONTROLLER_HPP_
#define SDL2_WRAPPER_EVENT_GAME_CONTROLLER_HPP_

#include <string>

namespace sdl { inline namespace event {

class game_controller final : public sdl::detail::resource<SDL_GameController, decltype(&SDL_GameControllerClose)> {
public:
	enum class bind_type : std::underlying_type_t<SDL_GameControllerBindType> {
		none = SDL_CONTROLLER_BINDTYPE_NONE,
		button = SDL_CONTROLLER_BINDTYPE_BUTTON,
		axis = SDL_CONTROLLER_BINDTYPE_AXIS,
		hat = SDL_CONTROLLER_BINDTYPE_HAT
	};

	enum class axis_type : std::underlying_type_t<SDL_GameControllerAxis> {
		invalid = SDL_CONTROLLER_AXIS_INVALID,
		left_x = SDL_CONTROLLER_AXIS_LEFTX,
		left_y = SDL_CONTROLLER_AXIS_LEFTY,
		right_x = SDL_CONTROLLER_AXIS_RIGHTX,
		right_y = SDL_CONTROLLER_AXIS_RIGHTY,
		trigger_left = SDL_CONTROLLER_AXIS_TRIGGERLEFT,
		trigger_right = SDL_CONTROLLER_AXIS_TRIGGERRIGHT,
		max = SDL_CONTROLLER_AXIS_MAX
	};

	enum class button_type : std::underlying_type_t<SDL_GameControllerButton> {
		invalid = SDL_CONTROLLER_BUTTON_INVALID,
		a = SDL_CONTROLLER_BUTTON_A,
		b = SDL_CONTROLLER_BUTTON_B,
		x = SDL_CONTROLLER_BUTTON_X,
		y = SDL_CONTROLLER_BUTTON_Y,
		back = SDL_CONTROLLER_BUTTON_BACK,
		guide = SDL_CONTROLLER_BUTTON_GUIDE,
		start = SDL_CONTROLLER_BUTTON_START,
		leftstick = SDL_CONTROLLER_BUTTON_LEFTSTICK,
		rightstick = SDL_CONTROLLER_BUTTON_RIGHTSTICK,
		leftshoulder = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
		rightshoulder = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
		dpad_up = SDL_CONTROLLER_BUTTON_DPAD_UP,
		dpad_down = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
		dpad_left = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
		dpad_right = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
		max = SDL_CONTROLLER_BUTTON_MAX,
	};

	using bind_data = SDL_GameControllerButtonBind;

	static inline decltype(auto) make_resource(int joystick_index) {
		return resource::make_resource(SDL_GameControllerOpen, SDL_GameControllerClose, joystick_index);
	}

	static inline decltype(auto) make_resource_from_id(joystick::id joyid) {
		return resource::make_resource(SDL_GameControllerFromInstanceID, [](auto) {}, joyid);
	}

	static int load_mappings(SDL_RWops *rw, int freerw) noexcept { return SDL_GameControllerAddMappingsFromRW(rw, freerw); }

	static int load_mappings(const char *file) noexcept { return SDL_GameControllerAddMappingsFromFile(file); }

	static int add_mappings(const char *mappingString) noexcept { return SDL_GameControllerAddMapping(mappingString); }

	static char *mapping(const joystick::guid &guid) noexcept { return SDL_GameControllerMappingForGUID(guid); }

	static bool is_game_controller(int joystick_index) noexcept { return (SDL_IsGameController(joystick_index) == SDL_TRUE); }

	static std::string name(int joystick_index) noexcept { return SDL_GameControllerNameForIndex(joystick_index); }

	static event_state state(event_state state = event_state::query) noexcept {
		return static_cast<event_state>(SDL_GameControllerEventState(static_cast<int>(state)));
	}

	static void update() noexcept { return SDL_GameControllerUpdate(); }

	static axis_type axis_from_string(const char *pchString) noexcept {
		return static_cast<axis_type>(SDL_GameControllerGetAxisFromString(pchString));
	}

	static std::string axis_to_string(axis_type type) noexcept {
		return SDL_GameControllerGetStringForAxis(static_cast<SDL_GameControllerAxis>(type));
	}

	static button_type button_from_string(const char *pchString) noexcept {
		return static_cast<button_type>(SDL_GameControllerGetButtonFromString(pchString));
	}

	static std::string button_to_string(button_type type) noexcept {
		return SDL_GameControllerGetStringForButton(static_cast<SDL_GameControllerButton>(type));
	}

public:
	using resource::resource;
	using resource::operator=;

	game_controller() = default;

	explicit game_controller(int joystick_index) : resource(make_resource(joystick_index)) {}

	void create(int joystick_index) { reset(make_resource(joystick_index)); }

	char *mapping() const noexcept { return SDL_GameControllerMapping(get()); }

	std::string name() const noexcept { return SDL_GameControllerName(get()); }

	bool attached() const noexcept { return (SDL_GameControllerGetAttached(get()) == SDL_TRUE); }

	joystick joystick() const noexcept { return sdl::joystick(SDL_GameControllerGetJoystick(get())); }

	bind_data axis_bind(axis_type axis) const noexcept {
		return SDL_GameControllerGetBindForAxis(get(), static_cast<SDL_GameControllerAxis>(axis));
	}

	Sint16 axis(axis_type axis) const noexcept { return SDL_GameControllerGetAxis(get(), static_cast<SDL_GameControllerAxis>(axis)); }

	bind_data button_bind(button_type button) const noexcept {
		return SDL_GameControllerGetBindForButton(get(), static_cast<SDL_GameControllerButton>(button));
	}

	Sint16 button(button_type button) const noexcept { return SDL_GameControllerGetButton(get(), static_cast<SDL_GameControllerButton>(button)); }
};

} } // namespace sdl::event

#endif // SDL2_WRAPPER_EVENT_GAME_CONTROLLER_HPP_

