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

#ifndef SDL2_WRAPPER_EVENT_HAPTIC_HPP_
#define SDL2_WRAPPER_EVENT_HAPTIC_HPP_

#include <string>

namespace sdl { inline namespace event {

class haptic final : public sdl::detail::resource<SDL_Haptic, decltype(&SDL_HapticClose)> {
public:
	using direction = SDL_HapticDirection;
	using constant = SDL_HapticConstant;
	using periodic = SDL_HapticPeriodic;
	using condition = SDL_HapticCondition;
	using ramp = SDL_HapticRamp;
	using left_right = SDL_HapticLeftRight;
	using custom = SDL_HapticCustom;
	using effect = SDL_HapticEffect;
	using effect_id = int;

	enum class effect_type : decltype(effect::type) {
		constant = SDL_HAPTIC_CONSTANT,
		sine = SDL_HAPTIC_SINE,
		left_right = SDL_HAPTIC_LEFTRIGHT,
		triangle = SDL_HAPTIC_TRIANGLE,
		saw_tooth_up = SDL_HAPTIC_SAWTOOTHUP,
		saw_tooth_down = SDL_HAPTIC_SAWTOOTHDOWN,
		ramp = SDL_HAPTIC_RAMP,
		spring = SDL_HAPTIC_SPRING,
		damper = SDL_HAPTIC_DAMPER,
		inertia = SDL_HAPTIC_INERTIA,
		friction = SDL_HAPTIC_FRICTION,
		custom = SDL_HAPTIC_CUSTOM,
		gain = SDL_HAPTIC_GAIN,
		autocenter = SDL_HAPTIC_AUTOCENTER,
		status = SDL_HAPTIC_STATUS,
		pause = SDL_HAPTIC_PAUSE,
	};

	enum class direction_type : decltype(direction::type) {
		polar = SDL_HAPTIC_POLAR,
		cartesian = SDL_HAPTIC_CARTESIAN,
		spherical = SDL_HAPTIC_SPHERICAL,
	};

	static constexpr Uint32 infinity = SDL_HAPTIC_INFINITY;

	static inline decltype(auto) make_resource(int device_index) {
		return resource::make_resource(SDL_HapticOpen, SDL_HapticClose, device_index);
	}

	static inline decltype(auto) make_resource_from_mouse() {
		return resource::make_resource(SDL_HapticOpenFromMouse, [](auto) {});
	}

	static inline decltype(auto) make_resource_from_joystick(SDL_Joystick *joystick) {
		return resource::make_resource(SDL_HapticOpenFromJoystick, [](auto) {}, joystick);
	}

	static inline int count() noexcept { return SDL_NumHaptics(); }

	static inline std::string name(int device_index) noexcept { return SDL_HapticName(device_index); }

	static inline bool opened(int device_index) noexcept { return (SDL_HapticOpened(device_index) != 0); }

	static inline bool mouse_is_haptic() noexcept { return (SDL_MouseIsHaptic() == SDL_TRUE); }

	static inline bool joystick_is_haptic(SDL_Joystick *joystick) noexcept { return (SDL_JoystickIsHaptic(joystick) == SDL_TRUE); }

public:
	using resource::resource;
	using resource::operator=;

	haptic() = default;

	explicit haptic(int device_index) : resource(make_resource(device_index)) {}

	explicit haptic(mouse) : resource(make_resource_from_mouse()) {}

	explicit haptic(SDL_Joystick *joystick) : resource(make_resource_from_joystick(joystick)) {}

	void create(int device_index) { reset(make_resource(device_index)); }

	int index() const noexcept { return SDL_HapticIndex(get()); }

	int effects() const noexcept { return SDL_HapticNumEffects(get()); }

	int effects_playing() const noexcept { return SDL_HapticNumEffectsPlaying(get()); }

	unsigned int query() const noexcept { return SDL_HapticQuery(get()); }

	int axes() const noexcept { return SDL_HapticNumAxes(get()); }

	bool is_supported(effect &e) const noexcept { return (SDL_HapticEffectSupported(get(), &e) == SDL_TRUE); }

	effect_id create_effect(effect &e) const noexcept { return SDL_HapticNewEffect(get(), &e); }

	bool update_effect(effect_id id, effect &data) const noexcept { return (SDL_HapticUpdateEffect(get(), id, &data) == 0); }

	bool run_effect(effect_id id, Uint32 iterations) const noexcept { return (SDL_HapticRunEffect(get(), id, iterations) == 0); }

	bool stop_effect(effect_id id) const noexcept { return (SDL_HapticStopEffect(get(), id) == 0); }

	void destroy_effect(effect_id id) const noexcept { SDL_HapticDestroyEffect(get(), id); }

	int effect_status(effect_id id) const noexcept { return SDL_HapticGetEffectStatus(get(), id); }

	bool gain(int gain) const noexcept { return (SDL_HapticSetGain(get(), gain) == 0); }

	bool autocenter(int ac) const noexcept { return (SDL_HapticSetAutocenter(get(), ac) == 0); }

	bool pause() const noexcept { return (SDL_HapticPause(get()) == 0); }

	bool unpause() const noexcept { return (SDL_HapticUnpause(get()) == 0); }

	bool stop() const noexcept { return (SDL_HapticStopAll(get()) == 0); }

	bool is_rumble_supported() const noexcept { return (SDL_HapticRumbleSupported(get()) == SDL_TRUE); }

	bool init_rumble() const noexcept { return (SDL_HapticRumbleInit(get()) == 0); }

	bool play_rumble(float strength, Uint32 length) const noexcept { return (SDL_HapticRumblePlay(get(), strength, length) == 0); }

	bool stop_rumble() const noexcept { return (SDL_HapticRumbleStop(get()) == 0); }
};

} } // namespace sdl::event

#endif // SDL2_WRAPPER_EVENT_HAPTIC_HPP_

