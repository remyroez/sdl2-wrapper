
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
	sdl::log::error(sdl::log::category::error, "Error: %s", sdl::error::get());
}

} // namespace

int main(int argc, char* argv[])
{
	int result = 0;

	SDL_Event we;
	SDL_zero(we);
	we.type = static_cast<decltype(we.type)>(sdl::event_type::window);
	std::cout << "SDL_WindowEvent.type: "
		<< static_cast<decltype(we.type)>(sdl::window_event_traits<>::type(we))
		<< std::endl;

	std::cout << "SDL_KeyboardEvent ... event_category: "
		<< static_cast<int>(sdl::to_event_category<SDL_KeyboardEvent>())
		<< std::endl;

	std::cout << "sdl::window_event::id::changed: "
		<< static_cast<int>(sdl::window_event::id::changed)
		<< std::endl;

	auto power = sdl::power::get();
	std::cout << "power: { "
		<< "state: " << static_cast<int>(power.state) << ", "
		<< "seconds: " << static_cast<int>(power.seconds) << ", "
		<< "battery: " << static_cast<int>(power.battery) << " }"
		<< std::endl;

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
		sdl::hint::render_driver("opengl");
		auto hint = sdl::hint::render_driver();
		if (hint != nullptr) std::cout << hint << std::endl;

		auto base_path = sdl::filesystem::base_path();
		std::cout << "base path: " << base_path.get() << std::endl;

		auto pref_path = sdl::filesystem::pref_path("remyroez", "sdl2-wrapper");
		std::cout << "pref path: " << pref_path.get() << std::endl;

		auto text = sdl::clipboard::get();
		std::cout << "clipboard: " << text.get() << std::endl;

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

		sdl::mouse_cursor mc(sdl::mouse_cursor::system_mouse_cursor_type::hand);
		mc.set();

		sdl::game_controller gc(0);
		sdl::joystick js = gc.joystick();

		sdl::haptic haptic(js);
		if (haptic.is_rumble_supported()) {
			std::cout << "rumble supported!" << std::endl;
			haptic.init_rumble();
		}

		bool readed = false;
		bool writed = false;

		// main loop
		bool running = true;
		while (running) {
			sdl::event_handler::poll([&running](auto e) {
				auto type = sdl::event_traits::type(e);

				if (type == sdl::event_type::quit) {
					running = false;
				}

				std::cout << sdl::common_event_traits::timestamp(e) << std::endl;
			});

			if (sdl::keyboard::is_pressed(sdl::scancode::enter)) {
				std::cout << "enter!" << std::endl;
				haptic.play_rumble(1.0f, 1000);
			}

			if (sdl::keyboard::is_pressed(sdl::scancode::r) && !readed) {
				std::cout << "r! - read from text.txt" << std::endl;
				auto file = sdl::file("test.txt", "r+");
				auto size = static_cast<std::size_t>(file.size());
				if (size < 0) {
					// error
				} else {
					std::vector<char> buf;
					buf.resize(size + 1, '\0');
					file.read(buf.data(), sizeof(decltype(buf)::value_type), size);
					std::cout << "read: " << buf.data() << std::endl;
					readed = true;
				}
			}

			if (sdl::keyboard::is_pressed(sdl::scancode::w) && !writed) {
				std::cout << "w! - write for text.txt" << std::endl;
				auto file = sdl::file("test.txt", "w+");
				std::string buf = "Hello";
				file.write(buf.data(), sizeof(decltype(buf)::value_type), buf.size());
				writed = true;
			}

			if (js.button(0)) {
				std::cout << "joystick button 0" << std::endl;
			}

			renderer.clear(0x80, 0x80, 0x80);
			renderer.copy(texture);
			renderer.present();

			sdl::timer::delay(1000/60);
		}
	}

	sdl::quit();

	return result;
}