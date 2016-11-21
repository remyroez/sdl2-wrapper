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

#ifndef SDL2_WRAPPER_AUDIO_AUDIO_DRIVER_HPP_
#define SDL2_WRAPPER_AUDIO_AUDIO_DRIVER_HPP_

#include <string>
#include <vector>

namespace sdl { inline namespace audio {

class audio_driver final {
public:
	static int count() noexcept { return SDL_GetNumAudioDrivers(); }

	static audio_driver get(int index) { return audio_driver(SDL_GetAudioDriver(index)); }

	static audio_driver current() noexcept { return audio_driver(SDL_GetCurrentAudioDriver()); }

	static std::vector<audio_driver> enumerate() {
		std::vector<audio_driver> list;
		auto num = audio_driver::count();
		for (auto i = 0; i < num; ++i) {
			list.emplace_back(SDL_GetAudioDriver(i));
		}
		return list;
	}

public:
	audio_driver() : _name() {}

	explicit audio_driver(const char *name)
		: _name(name == nullptr ? "" : name) {}

	explicit audio_driver(const std::string &name) : _name(name) {}

	audio_driver(const audio_driver &rhs) : _name(rhs._name), _was_init(rhs._was_init) {}

	audio_driver(audio_driver &&rhs) noexcept : _name(std::move(rhs._name)), _was_init(rhs._was_init) {}

	~audio_driver() noexcept { if (was_init()) quit(); }

	audio_driver &operator=(const audio_driver &rhs) = delete;

	audio_driver &operator=(audio_driver &&rhs) noexcept {
		_name = std::move(rhs._name);
		_was_init = rhs._was_init;
		return *this;
	}

	bool was_init() const noexcept { return _was_init; }

	std::string &&name() && { return std::move(_name); }

	const std::string &name() const & { return _name; }

	bool is_default() const noexcept { return _name.empty(); }

	bool init() { return _was_init = (SDL_AudioInit(is_default() ? nullptr : name().c_str()) == 0); }

	void quit() { SDL_AudioQuit(); _was_init = false; }

private:
	bool _was_init = false;
	std::string _name;
};

} } // namespace sdl::audio

#endif // SDL2_WRAPPER_AUDIO_AUDIO_DRIVER_HPP_

