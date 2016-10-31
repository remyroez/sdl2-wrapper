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

#ifndef SDL2_WRAPPER_SYSTEM_ENDIAN_HPP_
#define SDL2_WRAPPER_SYSTEM_ENDIAN_HPP_

namespace sdl { inline namespace system {

constexpr bool is_lil_endian = (SDL_BYTEORDER == SDL_LIL_ENDIAN);

constexpr bool is_big_endian = (SDL_BYTEORDER == SDL_BIG_ENDIAN);

inline Uint16 swap_endianness(Uint16 x) noexcept { return SDL_Swap16(x); }
inline Uint32 swap_endianness(Uint32 x) noexcept { return SDL_Swap32(x); }
inline Uint64 swap_endianness(Uint64 x) noexcept { return SDL_Swap64(x); }
inline float swap_endianness(float x) noexcept { return SDL_SwapFloat(x); }

inline Uint16 to_native_endianness_le(Uint16 x) noexcept { return SDL_SwapLE16(x); }
inline Uint32 to_native_endianness_le(Uint32 x) noexcept { return SDL_SwapLE32(x); }
inline Uint64 to_native_endianness_le(Uint64 x) noexcept { return SDL_SwapLE64(x); }
inline float to_native_endianness_le(float x) noexcept { return SDL_SwapFloatLE(x); }

inline Uint16 to_native_endianness_be(Uint16 x) noexcept { return SDL_SwapBE16(x); }
inline Uint32 to_native_endianness_be(Uint32 x) noexcept { return SDL_SwapBE32(x); }
inline Uint64 to_native_endianness_be(Uint64 x) noexcept { return SDL_SwapBE64(x); }
inline float to_native_endianness_be(float x) noexcept { return SDL_SwapFloatBE(x); }

} } // namespace sdl2::system

#endif // SDL2_WRAPPER_SYSTEM_ENDIAN_HPP_

