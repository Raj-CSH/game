#ifndef CONFIG_H_
#define CONFIG_H_

#include <iostream>
#include <string>

#define GAME_VERSION_MAJOR 1
#define GAME_VERSION_MINOR 0
#define ROOT "/home/raj-csh/dev/game"

namespace Config {
  static std::ostream * const LOGF = &std::cerr;
  static std::string const ASSETS_DIR = ROOT"/assets/";
  static std::string const TESTF_DIR = ROOT"/src/tests/test_files/";
  static std::string const WIN_CAPT = "Game";
  static constexpr int WIN_W = 800;
  static constexpr int WIN_H = 600;
}

#endif
