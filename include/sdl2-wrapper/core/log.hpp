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

#ifndef SDL2_WRAPPER_CORE_LOG_HPP_
#define SDL2_WRAPPER_CORE_LOG_HPP_

namespace sdl { inline namespace core {

struct log final {
	enum class category : int {
		application = SDL_LOG_CATEGORY_APPLICATION,
		error = SDL_LOG_CATEGORY_ERROR,
		assert = SDL_LOG_CATEGORY_ASSERT,
		system = SDL_LOG_CATEGORY_SYSTEM,
		audio = SDL_LOG_CATEGORY_AUDIO,
		video = SDL_LOG_CATEGORY_VIDEO,
		render = SDL_LOG_CATEGORY_RENDER,
		input = SDL_LOG_CATEGORY_INPUT,
		test = SDL_LOG_CATEGORY_TEST,
		reserved1 = SDL_LOG_CATEGORY_RESERVED1,
		reserved2 = SDL_LOG_CATEGORY_RESERVED2,
		reserved3 = SDL_LOG_CATEGORY_RESERVED3,
		reserved4 = SDL_LOG_CATEGORY_RESERVED4,
		reserved5 = SDL_LOG_CATEGORY_RESERVED5,
		reserved6 = SDL_LOG_CATEGORY_RESERVED6,
		reserved7 = SDL_LOG_CATEGORY_RESERVED7,
		reserved8 = SDL_LOG_CATEGORY_RESERVED8,
		reserved9 = SDL_LOG_CATEGORY_RESERVED9,
		reserved10 = SDL_LOG_CATEGORY_RESERVED10,
		custom = SDL_LOG_CATEGORY_CUSTOM,
	};

	enum class priority : std::underlying_type_t<SDL_LogPriority> {
		verbose = SDL_LOG_PRIORITY_VERBOSE,
		debug = SDL_LOG_PRIORITY_DEBUG,
		information = SDL_LOG_PRIORITY_INFO,
		warning = SDL_LOG_PRIORITY_WARN,
		error = SDL_LOG_PRIORITY_ERROR,
		critical = SDL_LOG_PRIORITY_CRITICAL,
		num = SDL_NUM_LOG_PRIORITIES
	};

	using callback = SDL_LogOutputFunction;

	static void set_priorities(priority priority) noexcept { SDL_LogSetAllPriority(static_cast<SDL_LogPriority>(priority)); }

	static void category_priority(category category, priority priority) noexcept {
		SDL_LogSetPriority(static_cast<int>(category), static_cast<SDL_LogPriority>(priority));
	}

	static priority category_priority(category category) noexcept {
		return static_cast<priority>(SDL_LogGetPriority(static_cast<int>(category)));
	}

	static void reset_priorities() noexcept { SDL_LogResetPriorities(); }

	template <typename ...Args>
	static void printf(const char *fmt, Args &&...args) noexcept { SDL_Log(fmt, std::forward<Args>(args)...); }

	template <typename ...Args>
	static void verbose(category category, const char *fmt, Args &&...args) noexcept {
		SDL_LogVerbose(static_cast<int>(category), fmt, std::forward<Args>(args)...);
	}

	template <typename ...Args>
	static void debug(category category, const char *fmt, Args &&...args) noexcept {
		SDL_LogDebug(static_cast<int>(category), fmt, std::forward<Args>(args)...);
	}

	template <typename ...Args>
	static void information(category category, const char *fmt, Args &&...args) noexcept {
		SDL_LogInfo(static_cast<int>(category), fmt, std::forward<Args>(args)...);
	}

	template <typename ...Args>
	static void warning(category category, const char *fmt, Args &&...args) noexcept {
		SDL_LogWarn(static_cast<int>(category), fmt, std::forward<Args>(args)...);
	}

	template <typename ...Args>
	static void error(category category, const char *fmt, Args &&...args) noexcept {
		SDL_LogError(static_cast<int>(category), fmt, std::forward<Args>(args)...);
	}

	template <typename ...Args>
	static void critical(category category, const char *fmt, Args &&...args) noexcept {
		SDL_LogCritical(static_cast<int>(category), fmt, std::forward<Args>(args)...);
	}

	template <typename ...Args>
	static void message(category category, priority priority, const char *fmt, Args &&...args) noexcept {
		SDL_LogMessage(static_cast<int>(category), static_cast<SDL_LogPriority>(priority), fmt, std::forward<Args>(args)...);
	}

	template <typename ...Args>
	static void message(category category, priority priority, const char *fmt, va_list ap) noexcept {
		SDL_LogMessageV(static_cast<int>(category), static_cast<SDL_LogPriority>(priority), fmt, ap);
	}

	static void output(callback *pcallback, void **puserdata) noexcept { SDL_LogGetOutputFunction(pcallback, puserdata); }

	static void output(callback callback, void *userdata) noexcept { SDL_LogSetOutputFunction(callback, userdata); }
};

} } // namespace sdl::core

#endif // SDL2_WRAPPER_CORE_LOG_HPP_

