#include "image.cpp"

#include <>

#include <SDL.h>

#include "config.h"
#include "log.h"

namespace Image {
	SDL_Window ** get_win() {
		static SDL_Window ** win = new SDL_Window *;
		return win;
	}

	SDL_Surface ** get_surf() {
		static SDL_Surface ** surf = new SDL_Surface *;
		return surf;
	}

	SDL_Surface ** get_bg_surf() {
		static SDL_Surface ** bg_surf = new SDL_Surface *;
		return bg_surf;
	}

	std::unique_ptr<>
}

