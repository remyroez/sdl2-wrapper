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

#ifndef SDL2_WRAPPER_IO_FILE_HPP_
#define SDL2_WRAPPER_IO_FILE_HPP_

#include <memory>
#include <string>

namespace sdl { inline namespace io {

class file : public sdl::detail::resource<SDL_RWops, decltype(&SDL_FreeRW)> {
public:
	struct function final {
		function() = delete;
		~function() = delete;
		function(const function &) = delete;
		void operator =(const function &) = delete;

		using size = decltype(SDL_RWops::size);
		using seek = decltype(SDL_RWops::seek);
		using read = decltype(SDL_RWops::read);
		using write = decltype(SDL_RWops::write);
		using close = decltype(SDL_RWops::close);
	};

	enum class type : Uint32 {
		unknown = SDL_RWOPS_UNKNOWN,
		windows = SDL_RWOPS_WINFILE,
		stdio = SDL_RWOPS_STDFILE,
		android = SDL_RWOPS_JNIFILE,
		memory = SDL_RWOPS_MEMORY,
		memory_ro = SDL_RWOPS_MEMORY_RO,
	};

	enum class whence : int {
		set = RW_SEEK_SET,
		current = RW_SEEK_CUR,
		end = RW_SEEK_END,
	};

	static void handle_closer(handle p) {
		SDL_RWclose(p);
	}

	static inline decltype(auto) make_resource() {
		return resource::make_resource(SDL_AllocRW, SDL_FreeRW);
	}

	static inline decltype(auto) make_resource(const char* file, const char* mode) {
		return resource::make_resource(SDL_RWFromFile, handle_closer, file, mode);
	}

	static inline decltype(auto) make_resource(void *fp, bool autoclose) {
		return resource::make_resource(SDL_RWFromFP, handle_closer, fp, (autoclose ? SDL_TRUE : SDL_FALSE));
	}

	static inline decltype(auto) make_resource(void *mem, int size) {
		return resource::make_resource(SDL_RWFromMem, handle_closer, mem, size);
	}

	static inline decltype(auto) make_resource(const void *mem, int size) {
		return resource::make_resource(SDL_RWFromConstMem, handle_closer, mem, size);
	}

public:
	using resource::resource;
	using resource::operator=;

	file() : resource(make_resource()) {}

	file(const char* file, const char* mode) : resource(make_resource(file, mode)) {}

	file(void *fp, bool autoclose) : resource(make_resource(fp, autoclose)) {}

	file(void *mem, int size) : resource(make_resource(mem, size)) {}

	file(const void *mem, int size) : resource(make_resource(mem, size)) {}

	decltype(auto) size() { return SDL_RWsize(get()); }

	decltype(auto) seek(Sint64 offset, whence whence) { return SDL_RWseek(get(), offset, static_cast<int>(whence)); }

	decltype(auto) tell() { return SDL_RWtell(get()); }

	decltype(auto) read(void* ptr, std::size_t size, std::size_t maxnum) { return SDL_RWread(get(), ptr, size, maxnum); }

	decltype(auto) write(const void* ptr, std::size_t size, std::size_t num) { return SDL_RWwrite(get(), ptr, size, num); }

	bool close() { return (SDL_RWclose(get()) == 0); }

	decltype(auto) read() const noexcept { return SDL_ReadU8(get()); }

	template <typename T>
	T read_le() const noexcept { return 0; }

	template <>
	Uint16 read_le<Uint16>() const noexcept { return SDL_ReadLE16(get()); }

	template <>
	Uint32 read_le<Uint32>() const noexcept { return SDL_ReadLE32(get()); }

	template <>
	Uint64 read_le<Uint64>() const noexcept { return SDL_ReadLE64(get()); }

	template <typename T>
	T read_be() const noexcept { return 0; }

	template <>
	Uint16 read_be<Uint16>() const noexcept { return SDL_ReadBE16(get()); }

	template <>
	Uint32 read_be<Uint32>() const noexcept { return SDL_ReadBE32(get()); }

	template <>
	Uint64 read_be<Uint64>() const noexcept { return SDL_ReadBE64(get()); }

	decltype(auto) write(Uint8 value) const noexcept { return SDL_WriteU8(get(), value); }

	template <typename T>
	std::size_t write_le(T) const noexcept { return 0; }

	template <>
	std::size_t write_le<Uint16>(Uint16 value) const noexcept { return SDL_WriteLE16(get(), value); }

	template <>
	std::size_t write_le<Uint32>(Uint32 value) const noexcept { return SDL_WriteLE32(get(), value); }

	template <>
	std::size_t write_le<Uint64>(Uint64 value) const noexcept { return SDL_WriteLE64(get(), value); }

	template <typename T>
	std::size_t write_be(T) const noexcept { return 0; }

	template <>
	std::size_t write_be<Uint16>(Uint16 value) const noexcept { return SDL_WriteBE16(get(), value); }

	template <>
	std::size_t write_be<Uint32>(Uint32 value) const noexcept { return SDL_WriteBE32(get(), value); }

	template <>
	std::size_t write_be<Uint64>(Uint64 value) const noexcept { return SDL_WriteBE64(get(), value); }
};

} } // namespace sdl::io

#endif // SDL2_WRAPPER_IO_FILE_HPP_

