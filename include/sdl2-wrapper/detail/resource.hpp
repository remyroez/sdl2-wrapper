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

#ifndef SDL2_WRAPPER_DETAIL_RESOURCE_HPP_
#define SDL2_WRAPPER_DETAIL_RESOURCE_HPP_

#include <memory>

namespace sdl { namespace detail {

template <typename Resource, typename Releaser>
class resource {
public:
	using base = resource<Resource, Releaser>;

	using type = Resource;

	using type_ptr = type *;

	using handle = std::unique_ptr<type, Releaser>;

	resource() : _handle(nullptr, [](auto) {}) {}

	explicit resource(type_ptr p, typename handle::deleter_type deleter = nullptr)
		: _handle(p, (deleter != nullptr) ? deleter : [](auto) {}) {}

	explicit resource(const resource &rhs) = delete;

	explicit resource(base &&rhs) noexcept
		: _handle(std::move(rhs._handle)) {}

	explicit resource(handle &&rhs) noexcept
		: _handle(std::move(rhs)) {}

	virtual ~resource() = default;

	explicit operator bool() const { return valid(); }

	resource &operator =(const resource &rhs) = delete;

	resource &operator =(resource &&rhs) noexcept {
		if (&rhs != this) _handle = std::move(rhs._handle); return *this;
	}

	operator type_ptr() const { return get(); }

	type_ptr get() const noexcept { return _handle.get(); }

	bool valid() const noexcept { return (get() != nullptr); }

	void destroy() noexcept { _handle.reset(); }

protected:
	template <typename creator, typename deleter, typename... arguments>
	static auto make_resource(creator cfn, deleter dfn, arguments&&... args) {
		auto result = cfn(std::forward<arguments>(args)...);
		return std::unique_ptr<std::decay_t<decltype(*result)>, decltype(dfn)>(result, dfn);
	}

protected:
	handle _handle;
};

} } // namespace sdl::detail

#endif // SDL2_WRAPPER_DETAIL_RESOURCE_HPP_

