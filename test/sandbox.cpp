
#include <iostream>

#include <SDL2\SDL.h>
#include "sdl2-wrapper/sdl.hpp"

#include <SDL2\SDL_bits.h>
#include "sdl2-wrapper/system/bit.hpp"

namespace {

constexpr int kWindowWidth = 640;
constexpr int kWindowHeight = 480;

void printError()
{
	std::cerr << sdl::get_error() << std::endl;
}

} // namespace

int main(int argc, char* argv[])
{
	int result = 0;

	sdl::version version;
	std::cout << "linked version: "
		<< static_cast<int>(version.major) << "."
		<< static_cast<int>(version.minor) << "."
		<< static_cast<int>(version.patch) << std::endl;
	std::cout << "compiled version: "
		<< static_cast<int>(sdl::compiled_version.major) << "."
		<< static_cast<int>(sdl::compiled_version.minor) << "."
		<< static_cast<int>(sdl::compiled_version.patch) << std::endl;

	// init system
	if (!sdl::init(SDL_INIT_EVERYTHING)) {
		printError();
		return 1;

	} else {
		// create window
		sdl::window window("sandbox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ::kWindowWidth, ::kWindowHeight, 0);
		if (!window) {
			printError();
			SDL_Quit();
			return 1;
		}

		window.resizable(true);
		window.minimum_size(320, 240);
		//window.maximum_size(1280, 720);

		// create renderer
		sdl::renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (!renderer) {
			printError();
			SDL_Quit();
			return 1;
		}

		// create surface
		sdl::surface surface("test.bmp");
		if (!surface) {
			printError();
			SDL_Quit();
			return 1;
		}

		renderer.logical_size(surface.size());
		renderer.integer_scale(true);

		// create texture
		sdl::texture texture(renderer, surface);

		// free surface
		surface.destroy();

		// main loop
		while (1) {
			SDL_Event event;
			if (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					break;
				}
			}

			renderer.clear(0x80, 0x80, 0x80);
			renderer.copy(texture);
			renderer.present();
		}

		sdl::quit();
	}

	return result;
}