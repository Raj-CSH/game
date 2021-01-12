#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <functional>
#include <unordered_map>

#include <cstddef>

#include <SDL.h>

namespace Keyboard {
	struct Key {
		private:
			SDL_Keysym const m_keysym;
		public:
			Key(SDL_Keysym const & keysym);

			SDL_Keysym const & get_keysym() const;
			bool operator==(Key const & key) const;
	};

	struct KeyHasher {
		public:
			size_t operator()(Key const & key) const;
	};

	class KeyboardHandler {
		private:
			std::unordered_map<Key, std::function<void()>, KeyHasher> m_on_key;
		public:
			void set_handler(Key const key, std::function<void()> on_key);
			void operator()(Key const & keysym) const;
	};
};

#endif
