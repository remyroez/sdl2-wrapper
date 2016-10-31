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

#ifndef SDL2_WRAPPER_SYSTEM_CPU_HPP_
#define SDL2_WRAPPER_SYSTEM_CPU_HPP_

namespace sdl { inline namespace system {

namespace cpu
{
	constexpr int safe_cache_line_size = SDL_CACHELINE_SIZE;

	int cores() noexcept { return SDL_GetCPUCount(); }

	int cache_line_size() noexcept { return SDL_GetCPUCacheLineSize(); }

	bool has_rdtsc() noexcept { return (SDL_HasRDTSC() == SDL_TRUE); }
	bool has_altivec() noexcept { return (SDL_HasAltiVec() == SDL_TRUE); }
	bool has_mmx() noexcept { return (SDL_HasMMX() == SDL_TRUE); }
	bool has_3dnow() noexcept { return (SDL_Has3DNow() == SDL_TRUE); }
	bool has_sse() noexcept { return (SDL_HasSSE() == SDL_TRUE); }
	bool has_sse2() noexcept { return (SDL_HasSSE2() == SDL_TRUE); }
	bool has_sse3() noexcept { return (SDL_HasSSE3() == SDL_TRUE); }
	bool has_sse41() noexcept { return (SDL_HasSSE41() == SDL_TRUE); }
	bool has_sse42() noexcept { return (SDL_HasSSE42() == SDL_TRUE); }
	bool has_avx() noexcept { return (SDL_HasAVX() == SDL_TRUE); }
	bool has_avx2() noexcept { return (SDL_HasAVX2() == SDL_TRUE); }
}

int system_ram() noexcept { return SDL_GetSystemRAM(); }

} } // namespace sdl2::system

#endif // SDL2_WRAPPER_SYSTEM_CPU_HPP_

