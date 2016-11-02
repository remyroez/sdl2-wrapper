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

#ifndef SDL2_WRAPPER_VIDEO_VIDEO_DRIVER_HPP_
#define SDL2_WRAPPER_VIDEO_VIDEO_DRIVER_HPP_

#include <string>
#include <vector>

namespace sdl { inline namespace video {

class video_driver final {
public:
	static int count() noexcept { return SDL_GetNumVideoDrivers(); }

	static video_driver get(int index) noexcept { return video_driver(SDL_GetVideoDriver(index)); }

	static video_driver current() noexcept { return video_driver(SDL_GetCurrentVideoDriver()); }

	static std::vector<video_driver> enumerate() {
		std::vector<video_driver> list;
		auto num = video_driver::count();
		for (auto i = 0; i < num; ++i) {
			list.emplace_back(SDL_GetVideoDriver(i));
		}
		return list;
	}

	video_driver() : _name() {}

	explicit video_driver(const char *name)
		: _name(name == nullptr ? "" : name) {}

	explicit video_driver(const std::string &name) : _name(name) {}

	video_driver(const video_driver &rhs) : _name(rhs._name), _was_init(rhs._was_init) {}

	video_driver(video_driver &&rhs) noexcept : _name(std::move(rhs._name)), _was_init(rhs._was_init) {}

	~video_driver() noexcept { if (was_init()) quit(); }

	video_driver &operator=(const video_driver &rhs) = delete;

	video_driver &operator=(video_driver &&rhs) noexcept {
		_name = std::move(rhs._name);
		_was_init = rhs._was_init;
		return *this;
	}

	std::string &&name() && { return std::move(_name); }

	bool was_init() const noexcept { return _was_init; }

	const std::string &name() const & { return _name; }

	bool is_default() const noexcept { return _name.empty(); }

	bool init() { return _was_init = (SDL_VideoInit(is_default() ? nullptr : name().c_str()) == 0); }

	void quit() { SDL_VideoQuit(); _was_init = false; }

private:
	bool _was_init = false;
	std::string _name;
};

} } // namespace sdl::video

#endif // SDL2_WRAPPER_VIDEO_VIDEO_DRIVER_HPP_
