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

#ifndef SDL2_WRAPPER_VIDEO_RECT_HPP_
#define SDL2_WRAPPER_VIDEO_RECT_HPP_

namespace sdl { inline namespace video {

struct rect : public SDL_Rect {
	static bool point_in_rect(const SDL_Point *p, const SDL_Rect *r) noexcept { return (SDL_PointInRect(p, r) == SDL_TRUE); }

	static bool empty(const SDL_Rect *r) noexcept { return (SDL_RectEmpty(r) == SDL_TRUE); }

	static bool equals(const SDL_Rect *a, const SDL_Rect *b) noexcept { return (SDL_RectEquals(a, b) == SDL_TRUE); }

	static bool has_intersection(const SDL_Rect *a, const SDL_Rect *b) noexcept { return (SDL_HasIntersection(a, b) == SDL_TRUE); }

	static bool intersect_rect(const SDL_Rect *a, const SDL_Rect *b, SDL_Rect * result) noexcept { return (SDL_IntersectRect(a, b, result) == SDL_TRUE); }

	static void union_rect(const SDL_Rect *a, const SDL_Rect *b, SDL_Rect * result) noexcept { SDL_UnionRect(a, b, result); }

	static bool enclose_points(const SDL_Point * points, int count, const SDL_Rect * clip, SDL_Rect * result) noexcept {
		return (SDL_EnclosePoints(points, count, clip, result) == SDL_TRUE);
	}

	static bool intersect_rect_and_line(const SDL_Rect *rect, int *X1, int *Y1, int *X2, int *Y2) noexcept {
		return (SDL_IntersectRectAndLine(rect, X1, Y1, X2, Y2) == SDL_TRUE);
	}

	using position_type = decltype(SDL_Rect::x);
	using size_type = decltype(SDL_Rect::w);

public:
	using SDL_Rect::SDL_Rect;

	constexpr rect() : SDL_Rect{ 0, 0, 0, 0 } {}
	constexpr rect(position_type x, position_type y, size_type w, size_type h) : SDL_Rect{ x, y, w, h } {}
	constexpr rect(const point &begin, const point &end) : SDL_Rect{ begin.x, begin.y, end.x - begin.x, end.y - begin.y } {}
	constexpr rect(const SDL_Rect &rhs) : SDL_Rect(rhs) {}

	constexpr auto position() const { return point{ x, y }; }
	void position(position_type x, position_type y) { this->x = x; this->y = y; }
	void position(const point &p) { position(p.x, p.y); }

	constexpr auto size() const { return point{ w, h }; }
	void size(size_type width, size_type height) { w = width; h = height; }
	void size(const point &p) { size(p.x, p.y); }

	constexpr auto left() const { return x; }
	void left(position_type left) { x = left; }

	constexpr auto right() const { return x + w; }
	void right(position_type right) { w = right - x; }

	constexpr auto top() const { return y; }
	void top(position_type top) { y = top; }

	constexpr auto bottom() const { return y + h; }
	void bottom(position_type bottom) { h = bottom - y; }

	constexpr auto begin() const { return point{ left(), top() }; }
	void begin(position_type px, position_type py) { left(px); top(py); }
	void begin(const point &p) { begin(p.x, p.y); }

	constexpr auto end() const { return point{ right(), bottom() }; }
	void end(position_type px, position_type py) { right(px); bottom(py); }
	void end(const point &p) { end(p.x, p.y); }

	bool operator ==(const rect &rhs) const noexcept { return (equals(this, &rhs) == SDL_TRUE); }

	bool point_in_rect(const point &p) const noexcept { return point_in_rect(&p, this); }

	bool empty() const noexcept { return empty(this); }

	bool has_intersection(const rect &b) const noexcept { return (has_intersection(this, &b) == SDL_TRUE); }

	bool intersect(const rect &b, rect &out) const noexcept { return (intersect_rect(this, &b, &out) == SDL_TRUE); }

	bool intersect(int* X1, int* Y1, int* X2, int* Y2) const noexcept { return (intersect_rect_and_line(this, X1, Y1, X2, Y2) == SDL_TRUE); }

	bool intersect(point &p1, point &p2) const noexcept { return intersect(&p1.x, &p1.y, &p2.x, &p2.y); }
};

} } // namespace sdl::video

#endif // SDL2_WRAPPER_VIDEO_RECT_HPP_

