#include <functional>
#include <memory>
#include <iostream>

#include <cstdlib>

#include <CLI11.hpp>
#include <SDL.h>

#include "config.h"
#include "keyboard.h"
#include "log.h"
#include "util.h"
#include "tests/run_tests.h"

void on_a() {
	Log::log(Log::INFO, "Wow you pressed the a key");
}

Keyboard::KeyboardHandler * get_kbd_handler() {
	static Keyboard::KeyboardHandler * kbd_handler = new Keyboard::KeyboardHandler;
	return kbd_handler;
}

void init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		Util::log_sdl_error("SDL failed to initialize.");
		exit(EXIT_FAILURE);
	}
	Log::log(Log::INFO, "Initialized SDL.");

	SDL_Window ** win = get_win();
	*win = SDL_CreateWindow(Config::WIN_CAPT.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Config::WIN_W, Config::WIN_H, SDL_WINDOW_SHOWN);

	if (!(*win)) {
		Util::log_sdl_error("Failed to construct window.");
		exit(EXIT_FAILURE);
	}
	Log::log(Log::INFO, "Constructed window.");

	SDL_Surface ** surf = get_surf();
	*surf = SDL_GetWindowSurface(*win);

	Keyboard::KeyboardHandler * kbd_handler =  get_kbd_handler();

	kbd_handler->set_handler(Keyboard::Key({SDL_SCANCODE_A, SDLK_a, 0}), std::function<void()>(on_a));
}

void quit() {
	SDL_FreeSurface(*get_surf());
	SDL_FreeSurface(*get_bg_surf());
	SDL_DestroyWindow(*get_win());
	SDL_Quit();
}

void load_bg() {
	std::string fpath = Config::ASSETS_DIR + "test.bmp";
	SDL_Surface ** bg_surf = get_bg_surf();
	*bg_surf = SDL_LoadBMP(fpath.c_str());
	if (!(*bg_surf)) {
		Util::logf_sdl_error("Failed to load image %s.", fpath.c_str());
		exit(EXIT_FAILURE);
	}
	Log::log(Log::INFO, "Loaded image.");
}

void cli(int argc, char ** argv) {
	CLI::App app("Game.");
	app.add_flag_callback("-t,--run-tests", RunTests::run_tests, "Run tests.");
	try {
		app.parse(argc, argv);
	} catch (const CLI::ParseError &e) {
		exit(app.exit(e));
	}
}

int main(int argc, char ** argv) {
	Log::init(Log::DEBUG, Config::LOGF);
	cli(argc, argv);
	init();
	load_bg();
	SDL_Window * win = *get_win();
	SDL_Surface * surf = *get_surf();
	SDL_Surface * bg_surf = *get_bg_surf();
	Keyboard::KeyboardHandler kbd_handler = *get_kbd_handler();
	SDL_Rect area = {0, 0, 900, 508};
	SDL_Event ev;
	bool running = true;

	SDL_BlitSurface(bg_surf, nullptr, surf, &area);
	SDL_UpdateWindowSurface(win);

	while (running) {
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT)
				running = false;
			else if (ev.type == SDL_KEYDOWN) {
				kbd_handler(Keyboard::Key(ev.key.keysym));
			}
		}
	}

	quit();

	return 0;
}

