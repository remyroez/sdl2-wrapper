
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

	auto c = sdl::color::yellow();
	std::cout << "color: "
		<< static_cast<int>(c.r) << ", "
		<< static_cast<int>(c.g) << ", "
		<< static_cast<int>(c.b) << ", "
		<< static_cast<int>(c.a)
		<< std::endl;

	c *= 0.3f;
	std::cout << "color2: "
		<< static_cast<int>(c.r) << ", "
		<< static_cast<int>(c.g) << ", "
		<< static_cast<int>(c.b) << ", "
		<< static_cast<int>(c.a)
		<< std::endl;

	// video driver
	{
		std::cout << "video driver" << std::endl;
		auto vdlist = sdl::video_driver::enumerate();
		int index = 0;
		for (auto &driver : vdlist) {
			std::cout << "\t" << index << ": " << driver.name() << std::endl;
			index++;
		}
	}

	// init system
	if (!sdl::init(SDL_INIT_EVERYTHING)) {
		printError();
		return 1;

	} else {
		// current video driver
		auto vd = sdl::video_driver::current();
		std::cout << "current video driver: " << vd.name() << std::endl;

		// display
		{
			auto display_list = sdl::display::enumerate();
			std::cout << "display: " << display_list.size() << std::endl;
			for (auto &display : display_list) {
				std::cout << "\t" << display.index() << std::endl;

				// display mode
				int index = 0;
				auto mode_list = display.enumerate_modes();
				for (auto &mode : mode_list) {
					std::cout << "\t\t" << index << ": {"
						<< "format: " << mode.format << ", "
						<< "w: " << mode.w << ", "
						<< "h: " << mode.h << ", "
						<< "refresh_rate: " << mode.refresh_rate << " }"
						<< std::endl;
					index++;
				}
			}
		}

		// create window
		sdl::window window_temp("sandbox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ::kWindowWidth, ::kWindowHeight, 0);

		sdl::window window;
		window = std::move(window_temp);
		if (!window) {
			printError();
			SDL_Quit();
			return 1;
		}

		window.resizable(true);
		window.minimum_size(320, 240);
		//window.maximum_size(1280, 720);

		auto window_display_index = window.display_index();
		auto window_display_mode = window.display_mode();

		std::cout << "window display(" << window_display_index << ") { "
			<< "format: " << window_display_mode.format << ", "
			<< "w: " << window_display_mode.w << ", "
			<< "h: " << window_display_mode.h << ", "
			<< "refresh_rate: " << window_display_mode.refresh_rate << " }"
			<< std::endl;

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

		sdl::message_box msgbox("title", "message");
		msgbox.push_button(0, "button1", sdl::message_box::button_flag::return_default);
		msgbox.push_button(1, "button2");
		msgbox.push_button(2, "button3", sdl::message_box::button_flag::escape_default);
		msgbox.push_button(3, "button4");
		msgbox.push_button(4, "button5");
		auto id = msgbox.show();
		std::cout << "message box selected: " << id << std::endl;

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