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

#ifndef SDL2_WRAPPER_SYSTEM_VERSION_HPP_
#define SDL2_WRAPPER_SYSTEM_VERSION_HPP_

namespace sdl { inline namespace system {

struct version {
	Uint8 major;
	Uint8 minor;
	Uint8 patch;

	version() {
		SDL_version v;
		SDL_GetVersion(&v);
		reset(v);
	}

	version(const SDL_version &v) {
		reset(v);
	}

	constexpr version(int major, int minor, int patch) : major(major), minor(minor), patch(patch) {}

	constexpr Uint32 value() const noexcept { return SDL_VERSIONNUM(major, minor, patch); }

	constexpr bool at_least() const noexcept { return SDL_VERSION_ATLEAST(major, minor, patch); }

	void reset(int major, int minor, int patch) noexcept {
		major = major;
		minor = minor;
		patch = patch;
	}

	void reset(const SDL_version &v) noexcept {
		major = v.major;
		minor = v.minor;
		patch = v.patch;
	}

	version &operator =(const SDL_version &rhs) noexcept { reset(rhs); }

	version &operator =(const version &rhs) noexcept = default;
};

constexpr version compiled_version { SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL };

const char *revision() noexcept { return SDL_GetRevision(); }

int revision_number() noexcept { return SDL_GetRevisionNumber(); }

} } // namespace sdl2::system

#endif // SDL2_WRAPPER_SYSTEM_VERSION_HPP_

