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

#ifndef SDL2_WRAPPER_AUDIO_SOUND_HPP_
#define SDL2_WRAPPER_AUDIO_SOUND_HPP_

#include <string>

namespace sdl { inline namespace audio {

class sound final {
public:
	using buffer_type = Uint8;
	using size_type = Uint32;

	static bool load(SDL_RWops *src, bool freesrc, audio_spec *spec, buffer_type **audio_buf, size_type *audio_len) noexcept {
		return (SDL_LoadWAV_RW(src, (freesrc ? 1 : 0), spec, audio_buf, audio_len) != nullptr);
	}

	static bool load(std::string path, audio_spec *spec, buffer_type **audio_buf, size_type *audio_len) noexcept {
		return (SDL_LoadWAV(path.c_str(), spec, audio_buf, audio_len) != nullptr);
	}

	static void free(buffer_type *audio_buf) noexcept { SDL_FreeWAV(audio_buf); }

public:
	sound() = default;

	sound(const sound &) = delete;

	sound(sound &&rhs) : _spec(rhs._spec), _buffer(rhs._buffer), _length(rhs._length) {}

	~sound() { free(); }

	const audio_spec &spec() const noexcept { return _spec; }

	auto frequency() const noexcept { return spec().freq; }
	auto format() const noexcept { return spec().format; }
	auto channels() const noexcept { return spec().channels; }
	auto silence() const noexcept { return spec().silence; }
	auto samples() const noexcept { return spec().samples; }
	auto padding() const noexcept { return spec().padding; }
	auto size() const noexcept { return spec().size; }
	auto callback() const noexcept { return spec().callback; }
	auto userdata() const noexcept { return spec().userdata; }

	buffer_type *buffer() noexcept { return _buffer; }

	const buffer_type *buffer() const noexcept { return _buffer; }

	audio_convert &convert_info() noexcept { return _convert; }

	const audio_convert &convert_info() const noexcept { return _convert; }

	size_type length() const noexcept { return _length; }

	size_type position() const noexcept { return _position; }

	void position(size_type pos) noexcept { _position = pos; }

	bool load(SDL_RWops *src, bool freesrc = true) noexcept {
		return load(src, freesrc, &_spec, &_buffer, &_length);
	}

	bool load(std::string path) noexcept {
		return load(path, &_spec, &_buffer, &_length);
	}

	void free() noexcept { free(_buffer); _buffer = nullptr; }

	void convert(buffer_type *buffer, size_type length) {
		_buffer = buffer;
		_length = length;
		_position = 0;
		_converted = true;
	}

private:
	audio_spec _spec;
	audio_convert _convert;
	buffer_type *_buffer = nullptr;
	size_type _length = 0;
	size_type _position = 0;
	bool _converted = false;
};

} } // namespace sdl::audio

#endif // SDL2_WRAPPER_AUDIO_SOUND_HPP_

