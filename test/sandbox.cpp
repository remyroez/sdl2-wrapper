
#include <iostream>

#include <SDL2\SDL.h>

#include "sdl2-wrapper/sdl.hpp"

namespace {

constexpr int kWindowWidth = 640;
constexpr int kWindowHeight = 480;

void printError()
{
	std::cerr << SDL_GetError() << std::endl;
}

} // namespace

int main(int argc, char* argv[])
{
	int result = 0;

	// init system
	if (!sdl::init(SDL_INIT_EVERYTHING)) {
		printError();
		return 1;

	}
	else {
		// create window
		sdl::video::window window("sandbox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ::kWindowWidth, ::kWindowHeight, 0);
		if (!window) {
			printError();
			SDL_Quit();
			return 1;
		}

		window.resizable(true);
		window.minimum_size(320, 240);
		window.maximum_size(640, 480);

		// create renderer
		auto renderer = sdl::video::make_renderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == nullptr)
		{
			printError();
			SDL_Quit();
			return 1;
		}

		// create surface
		auto surface = sdl::video::make_surface("test.bmp");
		if (surface == nullptr)
		{
			printError();
			SDL_Quit();
			return 1;
		}

		// create texture
		auto texture = sdl::video::make_texture(renderer.get(), surface.get());

		// free surface
		surface.reset();

		// main loop
		while (1)
		{
			SDL_Event event;
			if (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					break;
				}
			}

			SDL_SetRenderDrawColor(renderer.get(), 0x80, 0x80, 0x80, 0xFF);
			SDL_RenderClear(renderer.get());
			SDL_RenderCopy(renderer.get(), texture.get(), nullptr, nullptr);
			SDL_RenderPresent(renderer.get());
		}

		sdl::quit();
	}

	return result;
}