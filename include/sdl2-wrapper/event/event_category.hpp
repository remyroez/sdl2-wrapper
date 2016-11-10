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

#ifndef SDL2_WRAPPER_EVENT_EVENT_CATEGORY_HPP_
#define SDL2_WRAPPER_EVENT_EVENT_CATEGORY_HPP_

namespace sdl { inline namespace event {

enum class event_category : int {
	common,

	quit,
	window,
	syswm,
	keyboard,
	text_editing,
	text_input,

	mouse_motion,
	mouse_button,
	mouse_wheel,

	joy_axis,
	joy_ball,
	joy_hat,
	joy_button,
	joy_device,

	controller_axis,
	controller_button,
	controller_device,

	touch_finger,

	dollar_gesture,
	multi_gesture,

	drop,

	audio_device,

	user,

	invalid,
};

template <class T, detail::concept_is_same<T, SDL_QuitEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::quit; }

template <class T, detail::concept_is_same<T, SDL_WindowEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::window; }

template <class T, detail::concept_is_same<T, SDL_SysWMEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::syswm; }

template <class T, detail::concept_is_same<T, SDL_KeyboardEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::keyboard; }

template <class T, detail::concept_is_same<T, SDL_TextEditingEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::text_editing; }

template <class T, detail::concept_is_same<T, SDL_TextInputEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::text_input; }

template <class T, detail::concept_is_same<T, SDL_MouseMotionEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::mouse_motion; }

template <class T, detail::concept_is_same<T, SDL_MouseButtonEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::mouse_button; }

template <class T, detail::concept_is_same<T, SDL_MouseWheelEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::mouse_wheel; }

template <class T, detail::concept_is_same<T, SDL_JoyAxisEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::joy_axis; }

template <class T, detail::concept_is_same<T, SDL_JoyBallEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::joy_ball; }

template <class T, detail::concept_is_same<T, SDL_JoyHatEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::joy_hat; }

template <class T, detail::concept_is_same<T, SDL_JoyButtonEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::joy_button; }

template <class T, detail::concept_is_same<T, SDL_JoyDeviceEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::joy_device; }

template <class T, detail::concept_is_same<T, SDL_ControllerAxisEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::controller_axis; }

template <class T, detail::concept_is_same<T, SDL_ControllerButtonEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::controller_button; }

template <class T, detail::concept_is_same<T, SDL_ControllerDeviceEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::controller_device; }

template <class T, detail::concept_is_same<T, SDL_TouchFingerEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::touch_finger; }

template <class T, detail::concept_is_same<T, SDL_DollarGestureEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::dollar_gesture; }

template <class T, detail::concept_is_same<T, SDL_MultiGestureEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::multi_gesture; }

template <class T, detail::concept_is_same<T, SDL_DropEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::drop; }

template <class T, detail::concept_is_same<T, SDL_AudioDeviceEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::audio_device; }

template <class T, detail::concept_is_same<T, SDL_UserEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::user; }

template <class T, detail::concept_is_same<T, SDL_CommonEvent> = nullptr>
constexpr inline event_category to_event_category() { return event_category::common; }

template <event_type T, detail::concept_t<is_quit_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::quit; }

template <event_type T, detail::concept_t<is_window_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::window; }

template <event_type T, detail::concept_t<is_syswm_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::syswm; }

template <event_type T, detail::concept_t<is_keyboard_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::keyboard; }

template <event_type T, detail::concept_t<is_text_editing_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::text_editing; }

template <event_type T, detail::concept_t<is_text_input_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::text_input; }

template <event_type T, detail::concept_t<is_mouse_motion_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::mouse_motion; }

template <event_type T, detail::concept_t<is_mouse_button_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::mouse_button; }

template <event_type T, detail::concept_t<is_mouse_wheel_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::mouse_wheel; }

template <event_type T, detail::concept_t<is_joy_axis_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::joy_axis; }

template <event_type T, detail::concept_t<is_joy_ball_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::joy_ball; }

template <event_type T, detail::concept_t<is_joy_hat_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::joy_hat; }

template <event_type T, detail::concept_t<is_joy_button_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::joy_button; }

template <event_type T, detail::concept_t<is_joy_device_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::joy_device; }

template <event_type T, detail::concept_t<is_controller_axis_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::controller_axis; }

template <event_type T, detail::concept_t<is_controller_button_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::controller_button; }

template <event_type T, detail::concept_t<is_controller_device_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::controller_device; }

template <event_type T, detail::concept_t<is_touch_finger_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::touch_finger; }

template <event_type T, detail::concept_t<is_dollar_gesture_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::dollar_gesture; }

template <event_type T, detail::concept_t<is_multi_gesture_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::multi_gesture; }

template <event_type T, detail::concept_t<is_drop_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::drop; }

template <event_type T, detail::concept_t<is_audio_device_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::audio_device; }

template <event_type T, detail::concept_t<is_user_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::user; }

template <event_type T, detail::concept_t<is_valid_event<T>> = nullptr>
constexpr inline event_category to_event_category() { return event_category::common; }

constexpr event_category to_event_category(event_type type) {
	return 
		is_quit_event_type(type) ? event_category::quit
		: is_window_event_type(type) ? event_category::window
		: is_syswm_event_type(type) ? event_category::syswm
		: is_keyboard_event_type(type) ? event_category::keyboard
		: is_text_editing_event_type(type) ? event_category::text_editing
		: is_text_input_event_type(type) ? event_category::text_input
		: is_mouse_motion_event_type(type) ? event_category::mouse_motion
		: is_mouse_button_event_type(type) ? event_category::mouse_button
		: is_mouse_wheel_event_type(type) ? event_category::mouse_wheel
		: is_joy_axis_event_type(type) ? event_category::joy_axis
		: is_joy_ball_event_type(type) ? event_category::joy_ball
		: is_joy_hat_event_type(type) ? event_category::joy_hat
		: is_joy_button_event_type(type) ? event_category::joy_button
		: is_joy_device_event_type(type) ? event_category::joy_device
		: is_controller_axis_event_type(type) ? event_category::controller_axis
		: is_controller_button_event_type(type) ? event_category::controller_button
		: is_controller_device_event_type(type) ? event_category::controller_device
		: is_touch_finger_event_type(type) ? event_category::touch_finger
		: is_dollar_gesture_event_type(type) ? event_category::dollar_gesture
		: is_multi_gesture_event_type(type) ? event_category::multi_gesture
		: is_drop_event_type(type) ? event_category::drop
		: is_audio_device_event_type(type) ? event_category::audio_device
		: is_user_event_type(type) ? event_category::user
		: is_valid_event_type(type) ? event_category::common
		: event_category::invalid;
}

template <event_category T>
using event_category_data =
	std::conditional_t<(T == event_category::quit), SDL_QuitEvent,
	std::conditional_t<(T == event_category::window), SDL_WindowEvent,
	std::conditional_t<(T == event_category::syswm), SDL_SysWMEvent,
	std::conditional_t<(T == event_category::keyboard), SDL_KeyboardEvent,
	std::conditional_t<(T == event_category::text_editing), SDL_TextEditingEvent,
	std::conditional_t<(T == event_category::text_input), SDL_TextInputEvent,
	std::conditional_t<(T == event_category::mouse_motion), SDL_MouseMotionEvent,
	std::conditional_t<(T == event_category::mouse_button), SDL_MouseButtonEvent,
	std::conditional_t<(T == event_category::mouse_wheel), SDL_MouseWheelEvent,
	std::conditional_t<(T == event_category::joy_axis), SDL_JoyAxisEvent,
	std::conditional_t<(T == event_category::joy_ball), SDL_JoyBallEvent,
	std::conditional_t<(T == event_category::joy_hat), SDL_JoyHatEvent,
	std::conditional_t<(T == event_category::joy_button), SDL_JoyButtonEvent,
	std::conditional_t<(T == event_category::joy_device), SDL_JoyDeviceEvent,
	std::conditional_t<(T == event_category::controller_axis), SDL_ControllerAxisEvent,
	std::conditional_t<(T == event_category::controller_button), SDL_ControllerButtonEvent,
	std::conditional_t<(T == event_category::controller_device), SDL_ControllerDeviceEvent,
	std::conditional_t<(T == event_category::touch_finger), SDL_TouchFingerEvent,
	std::conditional_t<(T == event_category::dollar_gesture), SDL_DollarGestureEvent,
	std::conditional_t<(T == event_category::multi_gesture), SDL_MultiGestureEvent,
	std::conditional_t<(T == event_category::drop), SDL_DropEvent,
	std::conditional_t<(T == event_category::audio_device), SDL_AudioDeviceEvent,
	std::conditional_t<(T == event_category::user), SDL_UserEvent,
	std::conditional_t<(T == event_category::common), SDL_CommonEvent,
	void
>>>>>>>>>> >>>>>>>> >> >> >> ;

} } // namespace sdl2::event

#endif // SDL2_WRAPPER_EVENT_EVENT_CATEGORY_HPP_

