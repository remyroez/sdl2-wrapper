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

#ifndef SDL2_WRAPPER_CORE_HINT_HPP_
#define SDL2_WRAPPER_CORE_HINT_HPP_

namespace sdl { inline namespace core {

struct hint final {
	enum class priority : std::underlying_type_t<SDL_HintPriority> {
		default = SDL_HINT_DEFAULT,
		normal = SDL_HINT_NORMAL,
		override = SDL_HINT_OVERRIDE,
	};

	using hint_type = const char *;
	using value_type = const char *;
	using callback = SDL_HintCallback;

	static bool set(hint_type name, value_type value) noexcept { return (SDL_SetHint(name, value) == SDL_TRUE); }

	static bool set(hint_type name, value_type value, priority priority) noexcept {
		return (SDL_SetHintWithPriority(name, value, static_cast<SDL_HintPriority>(priority)) == SDL_TRUE);
	}

	static value_type get(hint_type name) noexcept { return SDL_GetHint(name); }

	static bool get(hint_type name, bool default_value) noexcept {
		return (SDL_GetHintBoolean(name, default_value ? SDL_TRUE : SDL_FALSE) == SDL_TRUE);
	}

	static void add_callback(hint_type name, callback callback, void *userdata = nullptr) noexcept {
		SDL_AddHintCallback(name, callback, userdata);
	}

	static void delete_callback(hint_type name, callback callback, void *userdata = nullptr) noexcept {
		SDL_DelHintCallback(name, callback, userdata);
	}

	static void clear() noexcept { SDL_ClearHints(); }

#define DEF_HINT(ID, NAME) \
	static constexpr hint_type id_ ## ID = NAME; \
	static bool ID(value_type value) noexcept { return set(id_ ## ID, value); } \
	static bool ID(value_type value, priority priority) noexcept { set(id_ ## ID, value, priority); } \
	static value_type ID() noexcept { return get(id_ ## ID); } \
	static bool ID(bool default_value) noexcept { return get(id_ ## ID, default_value); } \
	static void ID(callback callback, void *userdata = nullptr) noexcept { add_callback(id_ ## ID, callback, userdata); } \
	static void ID(std::nullptr_t, callback callback, void *userdata = nullptr) noexcept { delete_callback(id_ ## ID, callback, userdata); }

	DEF_HINT(framebuffer_acceleration, SDL_HINT_FRAMEBUFFER_ACCELERATION);
	DEF_HINT(render_driver, SDL_HINT_RENDER_DRIVER);
	DEF_HINT(render_opengl_shaders, SDL_HINT_RENDER_OPENGL_SHADERS);
	DEF_HINT(render_direct3d_threadsafe, SDL_HINT_RENDER_DIRECT3D_THREADSAFE);
	DEF_HINT(render_direct3d11_debug, SDL_HINT_RENDER_DIRECT3D11_DEBUG);
	DEF_HINT(render_scale_quality, SDL_HINT_RENDER_SCALE_QUALITY);
	DEF_HINT(render_vsync, SDL_HINT_RENDER_VSYNC);
	DEF_HINT(video_allow_screensaver, SDL_HINT_VIDEO_ALLOW_SCREENSAVER);
	DEF_HINT(video_x11_xvidmode, SDL_HINT_VIDEO_X11_XVIDMODE);
	DEF_HINT(video_x11_xinerama, SDL_HINT_VIDEO_X11_XINERAMA);
	DEF_HINT(video_x11_xrandr, SDL_HINT_VIDEO_X11_XRANDR);
	DEF_HINT(video_x11_net_wm_ping, SDL_HINT_VIDEO_X11_NET_WM_PING);
	DEF_HINT(window_frame_usable_while_cursor_hidden, SDL_HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN);
	DEF_HINT(windows_enable_messageloop, SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP);
	DEF_HINT(grab_keyboard, SDL_HINT_GRAB_KEYBOARD);
	DEF_HINT(mouse_relative_mode_warp, SDL_HINT_MOUSE_RELATIVE_MODE_WARP);
	DEF_HINT(mouse_focus_clickthrough, SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH);
	DEF_HINT(video_minimize_on_focus_loss, SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS);
	DEF_HINT(idle_timer_disabled, SDL_HINT_IDLE_TIMER_DISABLED);
	DEF_HINT(orientations, SDL_HINT_ORIENTATIONS);
	DEF_HINT(apple_tv_controller_ui_events, SDL_HINT_APPLE_TV_CONTROLLER_UI_EVENTS);
	DEF_HINT(apple_tv_remote_allow_rotation, SDL_HINT_APPLE_TV_REMOTE_ALLOW_ROTATION);
	DEF_HINT(accelerometer_as_joystick, SDL_HINT_ACCELEROMETER_AS_JOYSTICK);
	DEF_HINT(xinput_enabled, SDL_HINT_XINPUT_ENABLED);
	DEF_HINT(xinput_use_old_joystick_mapping, SDL_HINT_XINPUT_USE_OLD_JOYSTICK_MAPPING);
	DEF_HINT(gamecontrollerconfig, SDL_HINT_GAMECONTROLLERCONFIG);
	DEF_HINT(joystick_allow_background_events, SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS);
	DEF_HINT(allow_topmost, SDL_HINT_ALLOW_TOPMOST);
	DEF_HINT(timer_resolution, SDL_HINT_TIMER_RESOLUTION);
	DEF_HINT(thread_stack_size, SDL_HINT_THREAD_STACK_SIZE);
	DEF_HINT(video_highdpi_disabled, SDL_HINT_VIDEO_HIGHDPI_DISABLED);
	DEF_HINT(mac_ctrl_click_emulate_right_click, SDL_HINT_MAC_CTRL_CLICK_EMULATE_RIGHT_CLICK);
	DEF_HINT(video_win_d3dcompiler, SDL_HINT_VIDEO_WIN_D3DCOMPILER);
	DEF_HINT(video_window_share_pixel_format, SDL_HINT_VIDEO_WINDOW_SHARE_PIXEL_FORMAT);
	DEF_HINT(winrt_privacy_policy_url, SDL_HINT_WINRT_PRIVACY_POLICY_URL);
	DEF_HINT(winrt_privacy_policy_label, SDL_HINT_WINRT_PRIVACY_POLICY_LABEL);
	DEF_HINT(winrt_handle_back_button, SDL_HINT_WINRT_HANDLE_BACK_BUTTON);
	DEF_HINT(video_mac_fullscreen_spaces, SDL_HINT_VIDEO_MAC_FULLSCREEN_SPACES);
	DEF_HINT(mac_background_app, SDL_HINT_MAC_BACKGROUND_APP);
	DEF_HINT(android_apk_expansion_main_file_version, SDL_HINT_ANDROID_APK_EXPANSION_MAIN_FILE_VERSION);
	DEF_HINT(android_apk_expansion_patch_file_version, SDL_HINT_ANDROID_APK_EXPANSION_PATCH_FILE_VERSION);
	DEF_HINT(ime_internal_editing, SDL_HINT_IME_INTERNAL_EDITING);
	DEF_HINT(android_separate_mouse_and_touch, SDL_HINT_ANDROID_SEPARATE_MOUSE_AND_TOUCH);
	DEF_HINT(emscripten_keyboard_element, SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT);
	DEF_HINT(no_signal_handlers, SDL_HINT_NO_SIGNAL_HANDLERS);
	DEF_HINT(windows_no_close_on_alt_f4, SDL_HINT_WINDOWS_NO_CLOSE_ON_ALT_F4);
	DEF_HINT(bmp_save_legacy_format, SDL_HINT_BMP_SAVE_LEGACY_FORMAT);
	DEF_HINT(windows_disable_thread_naming, SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING);
	DEF_HINT(rpi_video_layer, SDL_HINT_RPI_VIDEO_LAYER);

#undef DEF_HINT
};

} } // namespace sdl::core

#endif // SDL2_WRAPPER_CORE_HINT_HPP_

