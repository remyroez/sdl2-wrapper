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

#include <type_traits>
#include <memory>

namespace sdl { namespace detail {

template <typename Handle, typename Releaser>
class resource {
public:
	using type = Handle;
	using handle = type *;
	using handle_holder = std::unique_ptr<type, Releaser>;

	resource() : _handle_holder(nullptr, [](auto) {}) {}

	explicit resource(handle p, typename handle_holder::deleter_type deleter = nullptr)
		: _handle_holder(p, (deleter != nullptr) ? deleter : [](auto) {}) {}

	explicit resource(const resource &rhs) = delete;

	explicit resource(resource &&rhs) noexcept
		: _handle_holder(std::move(rhs._handle_holder)) {}

	explicit resource(handle_holder &&rhs) noexcept
		: _handle_holder(std::move(rhs)) {}

	virtual ~resource() = default;

	explicit operator bool() const { return valid(); }

	resource &operator =(const resource &rhs) = delete;

	resource &operator =(resource &&rhs) noexcept {
		if (&rhs != this) reset(std::move(rhs._handle_holder)); return *this;
	}

	operator handle() const { return get(); }

	handle get() const noexcept { return _handle_holder.get(); }

	bool valid() const noexcept { return (get() != nullptr); }

	void reset(handle_holder &&hh) { _handle_holder = std::move(hh); }

	void destroy() noexcept { _handle_holder.reset(); }

protected:
	template <typename creator, typename deleter, typename... arguments>
	static auto make_resource(creator cfn, deleter dfn, arguments&&... args) {
		auto result = cfn(std::forward<arguments>(args)...);
		return handle_holder(result, dfn);
	}

protected:
	handle_holder _handle_holder;
};

} } // namespace sdl::detail

#endif // SDL2_WRAPPER_DETAIL_RESOURCE_HPP_

