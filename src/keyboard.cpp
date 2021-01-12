#include "keyboard.h"

#include <string>

#include <cstddef>

#include <SDL.h>

#include "log.h"

namespace Keyboard {
	Key::Key(SDL_Keysym const & keysym) : m_keysym(keysym) {}

	SDL_Keysym const & Key::get_keysym() const {
		return m_keysym;
	}

	bool Key::operator==(Key const & key) const {
		SDL_Keysym const & keysym =  key.get_keysym();
		return (m_keysym.sym == keysym.sym) && (m_keysym.mod == keysym.mod);
	}

	size_t KeyHasher::operator()(Key const & key) const {
		SDL_Keysym const & keysym = key.get_keysym();
		size_t res = 17;
		res = res * 31 + static_cast<size_t>(keysym.sym);
		res = res * 31 + keysym.mod;
		return res;
	}

	void KeyboardHandler::set_handler(Key const key, std::function<void()> on_key) {
		SDL_Keysym const & keysym = key.get_keysym();
		std::string key_name = SDL_GetKeyName(keysym.sym);
		std::string scan_name = SDL_GetScancodeName(keysym.scancode);

		Log::logf(Log::DEBUG, "Defining handler for physical key %s, virtual key %s.", scan_name.c_str(), key_name.c_str());

		if (m_on_key.count(key))
			Log::logf(Log::WARNING, "Redifining handler for key %s.", key_name.c_str());

		m_on_key[key] = on_key;
		Log::logf(Log::DEBUG, "Defined handler for key %s.", key_name.c_str());
	}

	void KeyboardHandler::operator()(Key const & key) const{
		SDL_Keysym const & keysym = key.get_keysym();
		std::string key_name = SDL_GetKeyName(keysym.sym);
		std::string scan_name = SDL_GetScancodeName(keysym.scancode);

		Log::logf(Log::DEBUG, "Handling physical key %s, virtual key %s.", scan_name.c_str(), key_name.c_str());
		if (m_on_key.count(key)) {
			Log::logf(Log::DEBUG, "Deferring to handler for key %s.", key_name.c_str());
			m_on_key.at(key)();
		} else {
			Log::logf(Log::WARNING, "Handler for key %s not defined!", key_name.c_str());
		}
	}
}

