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

#ifndef SDL2_WRAPPER_VIDEO_RENDERER_HPP_
#define SDL2_WRAPPER_VIDEO_RENDERER_HPP_

namespace sdl { inline namespace video {

class renderer final : public sdl::detail::resource<SDL_Renderer, decltype(&SDL_DestroyRenderer)>
{
public:
	static handle make_resource(SDL_Window* window, int index, Uint32 flags) {
		return base::make_resource(SDL_CreateRenderer, SDL_DestroyRenderer, window, index, flags);
	}

	static handle make_resource(SDL_Surface* surface) {
		return base::make_resource(SDL_CreateSoftwareRenderer, SDL_DestroyRenderer, surface);
	}

	explicit renderer(SDL_Window* window, int index, Uint32 flags)
		: base(make_resource(window, index, flags)) {}

	explicit renderer(SDL_Surface* surface)
		: base(make_resource(surface)) {}

	void create(SDL_Window* window, int index, Uint32 flags) {
		_handle = std::move(make_resource(window, index, flags));
	}

	void create(SDL_Surface* surface) {
		_handle = std::move(make_resource(surface));
	}

	bool render_info(SDL_RendererInfo *info) const noexcept { return (SDL_GetRendererInfo(get(), info) == 0); }

	point output_size() const noexcept { sdl::video::point result; SDL_GetRendererOutputSize(get(), &result.x, &result.y); return result; }

	SDL_Texture *create_texture(Uint32 format, int access, int w, int h) noexcept { return SDL_CreateTexture(get(), format, access, w, h); }

	SDL_Texture *create_texture_from_surface(SDL_Surface *surface) noexcept { return SDL_CreateTextureFromSurface(get(), surface); }

	bool render_target_supported() const noexcept { return (SDL_RenderTargetSupported(get()) == SDL_TRUE); }

	void render_target(SDL_Texture *texture) noexcept { SDL_SetRenderTarget(get(), texture); }

	SDL_Texture *render_target() const noexcept { return SDL_GetRenderTarget(get()); }

	void logical_size(int w, int h) noexcept { SDL_RenderSetLogicalSize(get(), w, h); }

	void logical_size(const point &size) noexcept { logical_size(size.x, size.y); }

	point logical_size() const noexcept { sdl::video::point result; SDL_RenderGetLogicalSize(get(), &result.x, &result.y); return result; }

	bool integer_scale(bool b) noexcept { return (SDL_RenderSetIntegerScale(get(), b ? SDL_TRUE : SDL_FALSE) == 0); }

	bool integer_scale() const noexcept { return (SDL_RenderGetIntegerScale(get()) == SDL_TRUE); }

	bool viewport(const SDL_Rect *rect) noexcept { return (SDL_RenderSetViewport(get(), rect) == 0); }

	rect viewport() const noexcept { sdl::video::rect result; SDL_RenderGetViewport(get(), &result); return result; }

	bool clip_rect(const SDL_Rect *rect) noexcept { return (SDL_RenderSetClipRect(get(), rect) == 0); }

	rect clip_rect() const noexcept { sdl::video::rect result; SDL_RenderGetClipRect(get(), &result); return result; }

	bool clip_enabled() const noexcept { return (SDL_RenderIsClipEnabled(get()) == SDL_TRUE); }

	bool scale(float x, float y) noexcept { return (SDL_RenderSetScale(get(), x, y) == 0); }

	void scale(float *x, float *y) const noexcept { SDL_RenderGetScale(get(), x, y); }

	bool draw_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) noexcept { return (SDL_SetRenderDrawColor(get(), r, g, b, a) == 0); }

	void draw_color(Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a) const noexcept { SDL_GetRenderDrawColor(get(), r, g, b, a); }

	bool blend_mode(SDL_BlendMode blendMode) noexcept { return (SDL_SetRenderDrawBlendMode(get(), blendMode) == 0); }

	bool blend_mode(SDL_BlendMode *blendMode) const noexcept { return (SDL_GetRenderDrawBlendMode(get(), blendMode) == 0); }

	SDL_BlendMode blend_mode() const noexcept { SDL_BlendMode result; blend_mode(&result); return result; }

	bool clear() noexcept { return (SDL_RenderClear(get()) == 0); }

	bool clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xFF) noexcept {
		Uint8 lr, lg, lb, la;
		draw_color(&lr, &lg, &lb, &la);
		draw_color(r, g, b, a);
		bool result = clear();
		draw_color(lr, lg, lb, la);
		return result;
	}

	bool draw_point(int x, int y) noexcept { return (SDL_RenderDrawPoint(get(), x, y) == 0); }

	bool draw_point(const point &point) noexcept { return draw_point(point.x, point.y); }

	bool draw_point(const SDL_Point *points, int count) noexcept { return (SDL_RenderDrawPoints(get(), points, count) == 0); }

	bool draw_line(int x1, int y1, int x2, int y2) noexcept { return (SDL_RenderDrawLine(get(), x1, y1, x2, y2) == 0); }

	bool draw_line(const point &begin, const point &end) noexcept { return draw_line(begin.x, begin.y, end.x, end.y); }

	bool draw_line(const SDL_Point *points, int count) noexcept { return (SDL_RenderDrawLines(get(), points, count) == 0); }

	bool draw_rect(const SDL_Rect *rect) noexcept { return (SDL_RenderDrawRect(get(), rect) == 0); }

	bool draw_rect(const rect &rect) noexcept { return draw_rect(&rect); }

	bool draw_rect(const SDL_Rect *rects, int count) noexcept { return (SDL_RenderDrawRects(get(), rects, count) == 0); }

	bool fill_rect(const SDL_Rect *rect) noexcept { return (SDL_RenderFillRect(get(), rect) == 0); }

	bool fill_rect(const rect &rect) noexcept { return fill_rect(&rect); }

	bool fill_rect(const SDL_Rect *rects, int count) noexcept { return (SDL_RenderFillRects(get(), rects, count) == 0); }

	bool copy(SDL_Texture *texture, const SDL_Rect *srcrect = nullptr, const SDL_Rect *dstrect = nullptr) noexcept {
		return (SDL_RenderCopy(get(), texture, srcrect, dstrect) == 0);
	}

	bool copy(
		SDL_Texture * texture,
		const SDL_Rect * srcrect,
		const SDL_Rect * dstrect,
		const double angle,
		const SDL_Point *center,
		const SDL_RendererFlip flip
	) noexcept {
		return (SDL_RenderCopyEx(get(), texture, srcrect, dstrect, angle, center, flip) == 0);
	}

	bool read_pixels(const SDL_Rect * rect, Uint32 format, void *pixels, int pitch) const noexcept {
		return (SDL_RenderReadPixels(get(), rect, format, pixels, pitch) == 0); 
	}

	void present() noexcept { SDL_RenderPresent(get()); }
};

} } // namespace sdl::video

#endif // SDL2_WRAPPER_VIDEO_RENDERER_HPP_

