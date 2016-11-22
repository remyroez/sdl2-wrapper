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

#ifndef SDL2_WRAPPER_AUDIO_AUDIO_DEVICE_HPP_
#define SDL2_WRAPPER_AUDIO_AUDIO_DEVICE_HPP_

#include <string>
#include <vector>

namespace sdl { inline namespace audio {

class audio_device final {
public:
	using id_type = SDL_AudioDeviceID;
	using name_type = const char *;

	enum class allowed_changes : int {
		frequency = SDL_AUDIO_ALLOW_FREQUENCY_CHANGE,
		format = SDL_AUDIO_ALLOW_FORMAT_CHANGE,
		channels = SDL_AUDIO_ALLOW_CHANNELS_CHANGE,
		any = SDL_AUDIO_ALLOW_ANY_CHANGE,
	};

	enum class status : std::underlying_type_t<SDL_AudioStatus> {
		stopped = SDL_AUDIO_STOPPED,
		playing = SDL_AUDIO_PLAYING,
		paused = SDL_AUDIO_PAUSED,
	};

	static constexpr id_type invalid_id = 0;
	static constexpr name_type default_device = nullptr;

	static int count(bool iscapture = false) noexcept { return SDL_GetNumAudioDevices(iscapture ? 1 : 0); }

	static name_type name(int index, bool iscapture = false) noexcept { return SDL_GetAudioDeviceName(index, iscapture ? 1 : 0); }

	static std::vector<std::string> enumerate(bool iscapture = false) {
		std::vector<std::string> list;
		auto num = count();
		for (auto i = 0; i < num; ++i) {
			list.emplace_back(name(i, iscapture));
		}
		return list;
	}

	static id_type open_device(const std::string &device, const audio_spec *pdesired, audio_spec *pobtained = nullptr, allowed_changes allowed_changes = allowed_changes::any, bool iscapture = false) noexcept {
		return SDL_OpenAudioDevice(
			(device.empty() ? nullptr : device.c_str()),
			(iscapture ? 1 : 0),
			pdesired,
			pobtained,
			((pobtained != nullptr) ? static_cast<int>(allowed_changes) : 0)
		);
	}

	static void close_device(id_type id) noexcept { SDL_CloseAudioDevice(id); }

	static int build_convert(audio_convert *cvt, audio_format src_format, Uint8 src_channels, int src_rate, audio_format dst_format, Uint8 dst_channels, int dst_rate) noexcept {
		return SDL_BuildAudioCVT(cvt, src_format, src_channels, src_rate, dst_format, dst_channels, dst_rate);
	}

	static bool convert(audio_convert *cvt) noexcept { return (SDL_ConvertAudio(cvt) == 0); }

	static void mix(Uint8 *dst, const Uint8 *src, audio_format format, Uint32 len, int volume = SDL_MIX_MAXVOLUME) noexcept {
		SDL_MixAudioFormat(dst, src, format, len, volume);
	}

public:
	audio_device() : _id(invalid_id) { SDL_zero(_spec); }

	audio_device(const audio_device &rhs) = delete;

	audio_device(audio_device &&rhs) noexcept : _id(rhs.release()), _spec(rhs._spec) {}

	~audio_device() = default;

	void open(const std::string &device, const audio_spec *pdesired, allowed_changes allowed_changes = allowed_changes::any, bool iscapture = false) {
		reset(open_device(device, pdesired, &_spec, allowed_changes, iscapture));
		_name = device;
		_iscapture = iscapture;
	}

	void open(const std::string &device, const audio_spec &desired, allowed_changes allowed_changes = allowed_changes::any, bool iscapture = false) {
		open(device, &desired, allowed_changes, iscapture);
	}

	void open(const audio_spec *pdesired, allowed_changes allowed_changes = allowed_changes::any, bool iscapture = false) {
		open(default_device, pdesired, allowed_changes, iscapture);
	}

	void open(const audio_spec &desired, allowed_changes allowed_changes = allowed_changes::any, bool iscapture = false) {
		open(&desired, allowed_changes, iscapture);
	}

	status current_status() const noexcept { return static_cast<status>(SDL_GetAudioDeviceStatus(id())); }

	void pause(bool b = true) noexcept { SDL_PauseAudioDevice(id(), b ? 1 : 0); }

	void resume() noexcept { pause(false); }

	bool queue(const void* data, Uint32 len) noexcept { return (SDL_QueueAudio(id(), data, len) == 0); }

	Uint32 dequeue(void* data, Uint32 len) noexcept { return (SDL_DequeueAudio(id(), data, len) == 0); }

	Uint32 queued_size() const noexcept { return SDL_GetQueuedAudioSize(id()); }

	void clear() noexcept { SDL_ClearQueuedAudio(id()); }

	void lock() noexcept { SDL_LockAudioDevice(id()); }

	void unlock() noexcept { SDL_UnlockAudioDevice(id()); }

	void close() noexcept { close_device(id()); _id = invalid_id; }

	id_type id() const noexcept { return _id; }

	const std::string &name() const noexcept { return _name; }

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

	bool is_capture() const noexcept { return _iscapture; }

	void reset() {
		close();
	}

	void reset(id_type new_id) {
		close();
		_id = new_id;
	}

	id_type release() noexcept { id_type result = id(); _id = invalid_id; return result; }

	bool valid() const noexcept { return (id() != invalid_id); }

	operator bool() const noexcept { return valid(); }

	audio_device &operator=(const audio_device &rhs) = delete;

	audio_device &operator =(audio_device &&rhs) noexcept {
		if (&rhs != this) reset(rhs.release());
		return *this;
	}

	bool convert(sound &sound) noexcept {
		bool result = false;

		audio_convert &cvt = sound.convert_info();

		build_convert(&cvt, sound.format(), sound.channels(), sound.frequency(), format(), channels(), frequency());

		if (cvt.needed) {
			cvt.buf = static_cast<Uint8 *>(SDL_malloc(sound.length() * cvt.len_mult));
			std::memcpy(cvt.buf, sound.buffer(), sound.length());
			cvt.len = sound.length();

			result = convert(&cvt);

			sound.free();

			lock();
			sound.convert(cvt.buf, cvt.len_cvt);
			unlock();

		} else {
			result = true;
		}

		return result;
	}

private:
	id_type _id;
	std::string _name;
	audio_spec _spec;
	bool _iscapture = false;
};

} } // namespace sdl::audio

#endif // SDL2_WRAPPER_AUDIO_AUDIO_DEVICE_HPP_

