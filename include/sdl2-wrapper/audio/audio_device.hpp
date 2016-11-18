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

public:
	audio_device() : _id(invalid_id) {}

	audio_device(id_type id) : _id(id) {}

	audio_device(const audio_device &rhs) = delete;

	audio_device(audio_device &&rhs) noexcept : _id(rhs.release()) {}

	audio_device(const std::string &device, const audio_spec *pdesired, audio_spec *pobtained = nullptr, allowed_changes allowed_changes = allowed_changes::any, bool iscapture = false)
		: _id(open_device(device, pdesired, pobtained, allowed_changes, iscapture)) {}

	audio_device(const std::string &device, const audio_spec &desired, audio_spec &obtained, allowed_changes allowed_changes = allowed_changes::any, bool iscapture = false)
		: audio_device(device, &desired, &obtained, allowed_changes, iscapture) {}

	audio_device(const audio_spec *pdesired, audio_spec *pobtained = nullptr, allowed_changes allowed_changes = allowed_changes::any, bool iscapture = false)
		: audio_device(default_device, pdesired, pobtained, allowed_changes, iscapture) {}

	audio_device(const audio_spec &desired, audio_spec &obtained, allowed_changes allowed_changes = allowed_changes::any, bool iscapture = false)
		: audio_device(&desired, &obtained, allowed_changes, iscapture) {}

	~audio_device() = default;

	void open(const std::string &device, const audio_spec *pdesired, audio_spec *pobtained = nullptr, allowed_changes allowed_changes = allowed_changes::any, bool iscapture = false) {
		reset(open_device(device, pdesired, pobtained, allowed_changes, iscapture));
	}

	void open(const std::string &device, const audio_spec &desired, audio_spec &obtained, allowed_changes allowed_changes = allowed_changes::any, bool iscapture = false) {
		open(device, &desired, &obtained, allowed_changes, iscapture);
	}

	void open(const audio_spec *pdesired, audio_spec *pobtained = nullptr, allowed_changes allowed_changes = allowed_changes::any, bool iscapture = false) {
		open(default_device, pdesired, pobtained, allowed_changes, iscapture);
	}

	void open(const audio_spec &desired, audio_spec &obtained, allowed_changes allowed_changes = allowed_changes::any, bool iscapture = false) {
		open(&desired, &obtained, allowed_changes, iscapture);
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

private:
	id_type _id;
};

} } // namespace sdl::audio

#endif // SDL2_WRAPPER_AUDIO_AUDIO_DEVICE_HPP_

