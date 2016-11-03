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

#ifndef SDL2_WRAPPER_EVENT_EVENT_HANDLER_HPP_
#define SDL2_WRAPPER_EVENT_EVENT_HANDLER_HPP_

namespace sdl { inline namespace event {

class event_handler {
	using event_filter = SDL_EventFilter;

	struct event_watcher {
		event_filter filter;
		void *userdata;
	};

	enum class action : std::underlying_type_t<SDL_eventaction> {
		add = SDL_ADDEVENT,
		peek = SDL_PEEKEVENT,
		get = SDL_GETEVENT
	};

	enum class state : int {
		query = SDL_QUERY,
		ignore = SDL_IGNORE,
		disable = SDL_DISABLE,
		enable = SDL_ENABLE
	};

	static inline void pump() noexcept { SDL_PumpEvents(); }

	static inline int peep_events(SDL_Event *events, int numevents, action action, Uint32 minType = SDL_FIRSTEVENT, Uint32 maxType = SDL_LASTEVENT) noexcept {
		SDL_PeepEvents(events, numevents, static_cast<SDL_eventaction>(action), minType, maxType);
	}

	template <typename T>
	static inline int peep_events(T &events, action action, Uint32 minType = SDL_FIRSTEVENT, Uint32 maxType = SDL_LASTEVENT) noexcept {
		peep_events(events.data(), events.size(), action, minType, maxType);
	}

	static inline bool has_event(Uint32 type) noexcept { return (SDL_HasEvent(type) == SDL_TRUE); }

	static inline bool has_events(Uint32 minType, Uint32 maxType) noexcept { return (SDL_HasEvents(minType, maxType) == SDL_TRUE); }

	static inline void flush_event(Uint32 type) noexcept { SDL_FlushEvent(type); }

	static inline void flush_events(Uint32 minType, Uint32 maxType) noexcept { SDL_FlushEvents(minType, maxType); }

	static inline bool poll(SDL_Event *event) noexcept { return (SDL_PollEvent(event) != 0); }

	static inline bool wait(SDL_Event *event) noexcept { return (SDL_WaitEvent(event) != 0); }

	static inline bool wait_timeout(SDL_Event *event, int timeout) noexcept { return (SDL_WaitEventTimeout(event, timeout) != 0); }

	static inline bool push(SDL_Event *event) noexcept { return (SDL_PushEvent(event) != 0); }

	static inline void set_filter(event_filter filter, void *userdata) noexcept { SDL_SetEventFilter(filter, userdata); }

	static inline bool get_filter(event_filter *filter, void **userdata) noexcept { return (SDL_GetEventFilter(filter, userdata) == SDL_TRUE); }

	static inline void add_watcher(event_filter watcher, void *userdata) noexcept { SDL_AddEventWatch(watcher, userdata); }

	static inline void add_watcher(event_watcher watcher) noexcept { add_watcher(watcher.filter, watcher.userdata); }

	static inline void delete_watcher(event_filter watcher, void *userdata) noexcept { SDL_DelEventWatch(watcher, userdata); }

	static inline void delete_watcher(event_watcher watcher) noexcept { delete_watcher(watcher.filter, watcher.userdata); }

	static inline void filter(event_filter filter, void *userdata) noexcept { SDL_FilterEvents(filter, userdata); }

	static inline state event_state(Uint32 type, state state = state::query) noexcept {
		return static_cast<event_handler::state>(SDL_EventState(type, static_cast<int>(state)));
	}

	static inline decltype(auto) register_events(int numevents) noexcept { return SDL_RegisterEvents(numevents); }
};

} } // namespace sdl2::system

#endif // SDL2_WRAPPER_EVENT_EVENT_HANDLER_HPP_

