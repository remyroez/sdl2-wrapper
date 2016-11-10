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

#ifndef SDL2_WRAPPER_EVENT_EVENT_HPP_
#define SDL2_WRAPPER_EVENT_EVENT_HPP_

#include <string>

namespace sdl { inline namespace event {

namespace event_detail {

template <typename T>
class event_data_holder {
public:
	using data_type = T;

	explicit constexpr event_data_holder(const data_type &data) : _data(data) {}
	explicit constexpr event_data_holder(const event_data_holder &rhs) = default;
	event_data_holder &operator =(const event_data_holder &rhs) = default;

	constexpr event_type type() const { static_cast<event_type>(_data.type); }

	constexpr const data_type &get() const { return _data; }

private:
	data_type _data;
};

template <typename T, typename U = T>
class basic_event_view : public event_data_holder<T> {};

template <typename T>
class basic_event_view<T, decltype(SDL_Event::common)> : public event_data_holder<T> {
public:
	using event_data_holder::event_data_holder;
	using event_data_holder::operator =;

	explicit constexpr basic_event_view(const SDL_Event &event) : event_data_holder(event.common) {}

	constexpr auto timestamp() const { return get().timestamp; }
};

template <typename T>
class basic_event_view<T, decltype(SDL_Event::window)> : public event_data_holder<T> {
public:
	using event_data_holder::event_data_holder;
	using event_data_holder::operator =;

	explicit constexpr basic_event_view(const SDL_Event &event) : event_data_holder(event.window) {}

	enum class id : std::underlying_type_t<SDL_WindowEventID> {
		none = SDL_WINDOWEVENT_NONE,        
		shown = SDL_WINDOWEVENT_SHOWN,       
		hidden = SDL_WINDOWEVENT_HIDDEN,      
		exposed = SDL_WINDOWEVENT_EXPOSED,     
									
		moved = SDL_WINDOWEVENT_MOVED,       
									
		resized = SDL_WINDOWEVENT_RESIZED,     
		changed = SDL_WINDOWEVENT_SIZE_CHANGED,				
									
		minimized = SDL_WINDOWEVENT_MINIMIZED,   
		maximized = SDL_WINDOWEVENT_MAXIMIZED,   
		restored = SDL_WINDOWEVENT_RESTORED,    
									
		enter = SDL_WINDOWEVENT_ENTER,       
		leave = SDL_WINDOWEVENT_LEAVE,       
		focus_gained = SDL_WINDOWEVENT_FOCUS_GAINED,
		focus_lost = SDL_WINDOWEVENT_FOCUS_LOST,  
		close = SDL_WINDOWEVENT_CLOSE,       
		take_focus = SDL_WINDOWEVENT_TAKE_FOCUS,  
		hit_test = SDL_WINDOWEVENT_HIT_TEST     
	};

	constexpr auto timestamp() const { return get().timestamp; }

	constexpr auto windowID() const { return get().windowID; }

	constexpr id event_id() const { return static_cast<id>(get().event); }

	constexpr auto data1() const { return get().data1; }
	constexpr auto data2() const { return get().data2; }

	constexpr auto moved_x() const { return data1(); }
	constexpr auto moved_y() const { return data2(); }

	constexpr auto resized_w() const { return data1(); }
	constexpr auto resized_h() const { return data2(); }

	constexpr auto changed_w() const { return data1(); }
	constexpr auto changed_h() const { return data2(); }
};

template <typename T>
class basic_event_view<T, decltype(SDL_Event::key)> : public event_data_holder<T> {
public:
	using event_data_holder::event_data_holder;
	using event_data_holder::operator =;

	explicit constexpr basic_event_view(const SDL_Event &event) : event_data_holder(event.key) {}

	constexpr auto timestamp() const { return get().timestamp; }

	constexpr auto windowID() const { return get().windowID; }
	constexpr auto state() const { return get().state; }
	constexpr auto repeat() const { return get().repeat; }

	constexpr auto keysym() const { return get().keysym; }

	constexpr auto scancode() const { return keysym().scancode; }
	constexpr auto sym() const { return keysym().sym; }
	constexpr auto mod() const { return keysym().mod; }
};

template <typename T>
class basic_event_view<T, decltype(SDL_Event::edit)> : public event_data_holder<T> {
public:
	using event_data_holder::event_data_holder;
	using event_data_holder::operator =;

	static constexpr std::size_t text_size = SDL_TEXTEDITINGEVENT_TEXT_SIZE;

	explicit constexpr basic_event_view(const SDL_Event &event) : event_data_holder(event.edit) {}

	constexpr auto timestamp() const { return get().timestamp; }

	constexpr auto windowID() const { return get().windowID; }

	constexpr std::string text() const { return get().text; }

	constexpr auto start() const { return get().start; }
	constexpr auto length() const { return get().length; }
};

template <typename T>
class basic_event_view<T, decltype(SDL_Event::text)> : public event_data_holder<T> {
public:
	using event_data_holder::event_data_holder;
	using event_data_holder::operator =;

	static constexpr std::size_t text_size = SDL_TEXTINPUTEVENT_TEXT_SIZE;

	explicit constexpr basic_event_view(const SDL_Event &event) : event_data_holder(event.text) {}

	constexpr auto timestamp() const { return get().timestamp; }

	constexpr auto windowID() const { return get().windowID; }

	constexpr std::string text() const { return get().text; }
};

template <typename T>
class basic_event_view<T, decltype(SDL_Event::motion)> : public event_data_holder<T> {
public:
	using event_data_holder::event_data_holder;
	using event_data_holder::operator =;

	explicit constexpr basic_event_view(const SDL_Event &event) : event_data_holder(event.motion) {}

	constexpr auto timestamp() const { return get().timestamp; }

	constexpr auto windowID() const { return get().windowID; }

	constexpr auto which() const { return get().which; }
	constexpr auto state() const { return get().state; }
	constexpr auto x() const { return get().x; }
	constexpr auto y() const { return get().y; }
	constexpr auto xrel() const { return get().xrel; }
	constexpr auto yrel() const { return get().yrel; }
};

} // namespace event_detail

template <event_type T = event_type::first>
using event_view = event_detail::basic_event_view<event_data<T>>;

using common_event = event_detail::basic_event_view<decltype(SDL_Event::common)>;
using window_event = event_detail::basic_event_view<decltype(SDL_Event::window)>;
using key_event = event_detail::basic_event_view<decltype(SDL_Event::key)>;
using text_editing_event = event_detail::basic_event_view<decltype(SDL_Event::edit)>;

template <typename T = std::nullptr_t>
struct basic_event_traits {
	using this_event = T;

	static constexpr const this_event &get(const this_event &t) { return t; }

	static constexpr event_type type(const SDL_Event &t) { return static_cast<event_type>(t.type); }

};

struct event_traits : basic_event_traits<> {};

struct common_event_traits : basic_event_traits<SDL_CommonEvent> {
	static constexpr const this_event &get(const SDL_Event &t) { return t.common; }

	static constexpr auto timestamp(const SDL_Event &t) { return get(t).timestamp; }
};

template <typename = SDL_WindowEvent>
struct window_event_traits;

template <>
struct window_event_traits<SDL_WindowEvent> : basic_event_traits<SDL_WindowEvent> {
	enum class id : std::underlying_type_t<SDL_WindowEventID> {
		none = SDL_WINDOWEVENT_NONE,
		shown = SDL_WINDOWEVENT_SHOWN,
		hidden = SDL_WINDOWEVENT_HIDDEN,
		exposed = SDL_WINDOWEVENT_EXPOSED,

		moved = SDL_WINDOWEVENT_MOVED,

		resized = SDL_WINDOWEVENT_RESIZED,
		changed = SDL_WINDOWEVENT_SIZE_CHANGED,

		minimized = SDL_WINDOWEVENT_MINIMIZED,
		maximized = SDL_WINDOWEVENT_MAXIMIZED,
		restored = SDL_WINDOWEVENT_RESTORED,

		enter = SDL_WINDOWEVENT_ENTER,
		leave = SDL_WINDOWEVENT_LEAVE,
		focus_gained = SDL_WINDOWEVENT_FOCUS_GAINED,
		focus_lost = SDL_WINDOWEVENT_FOCUS_LOST,
		close = SDL_WINDOWEVENT_CLOSE,
		take_focus = SDL_WINDOWEVENT_TAKE_FOCUS,
		hit_test = SDL_WINDOWEVENT_HIT_TEST
	};

	static constexpr const this_event &get(const SDL_Event &t) { return t.window; }

	static constexpr auto timestamp(const SDL_Event &t) { return get(t).timestamp; }

	static constexpr auto windowID(const SDL_Event &t) { return get(t).windowID; }

	static constexpr id event_id(const SDL_Event &t) { return static_cast<id>(get(t).event); }

	static constexpr auto data1(const SDL_Event &t) { return get(t).data1; }
	static constexpr auto data2(const SDL_Event &t) { return get(t).data2; }

	static constexpr auto moved_x(const SDL_Event &t) { return data1(t); }
	static constexpr auto moved_y(const SDL_Event &t) { return data2(t); }

	static constexpr auto resized_w(const SDL_Event &t) { return data1(t); }
	static constexpr auto resized_h(const SDL_Event &t) { return data2(t); }

	static constexpr auto changed_w(const SDL_Event &t) { return data1(t); }
	static constexpr auto changed_h(const SDL_Event &t) { return data2(t); }
};

} } // namespace sdl2::system

#endif // SDL2_WRAPPER_EVENT_EVENT_HPP_

