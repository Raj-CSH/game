# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/raj-csh/dev/game

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/raj-csh/dev/game/cmake

# Include any dependencies generated for this target.
include lib/SDL2/CMakeFiles/SDL2main.dir/depend.make

# Include the progress variables for this target.
include lib/SDL2/CMakeFiles/SDL2main.dir/progress.make

# Include the compile flags for this target's objects.
include lib/SDL2/CMakeFiles/SDL2main.dir/flags.make

lib/SDL2/CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.o: lib/SDL2/CMakeFiles/SDL2main.dir/flags.make
lib/SDL2/CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.o: ../lib/SDL2/src/main/dummy/SDL_dummy_main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/raj-csh/dev/game/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/SDL2/CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.o"
	cd /home/raj-csh/dev/game/cmake/lib/SDL2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.o -c /home/raj-csh/dev/game/lib/SDL2/src/main/dummy/SDL_dummy_main.c

lib/SDL2/CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.i"
	cd /home/raj-csh/dev/game/cmake/lib/SDL2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/raj-csh/dev/game/lib/SDL2/src/main/dummy/SDL_dummy_main.c > CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.i

lib/SDL2/CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.s"
	cd /home/raj-csh/dev/game/cmake/lib/SDL2 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/raj-csh/dev/game/lib/SDL2/src/main/dummy/SDL_dummy_main.c -o CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.s

# Object files for target SDL2main
SDL2main_OBJECTS = \
"CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.o"

# External object files for target SDL2main
SDL2main_EXTERNAL_OBJECTS =

lib/SDL2/libSDL2main.a: lib/SDL2/CMakeFiles/SDL2main.dir/src/main/dummy/SDL_dummy_main.c.o
lib/SDL2/libSDL2main.a: lib/SDL2/CMakeFiles/SDL2main.dir/build.make
lib/SDL2/libSDL2main.a: lib/SDL2/CMakeFiles/SDL2main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/raj-csh/dev/game/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libSDL2main.a"
	cd /home/raj-csh/dev/game/cmake/lib/SDL2 && $(CMAKE_COMMAND) -P CMakeFiles/SDL2main.dir/cmake_clean_target.cmake
	cd /home/raj-csh/dev/game/cmake/lib/SDL2 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SDL2main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/SDL2/CMakeFiles/SDL2main.dir/build: lib/SDL2/libSDL2main.a

.PHONY : lib/SDL2/CMakeFiles/SDL2main.dir/build

lib/SDL2/CMakeFiles/SDL2main.dir/clean:
	cd /home/raj-csh/dev/game/cmake/lib/SDL2 && $(CMAKE_COMMAND) -P CMakeFiles/SDL2main.dir/cmake_clean.cmake
.PHONY : lib/SDL2/CMakeFiles/SDL2main.dir/clean

lib/SDL2/CMakeFiles/SDL2main.dir/depend:
	cd /home/raj-csh/dev/game/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/raj-csh/dev/game /home/raj-csh/dev/game/lib/SDL2 /home/raj-csh/dev/game/cmake /home/raj-csh/dev/game/cmake/lib/SDL2 /home/raj-csh/dev/game/cmake/lib/SDL2/CMakeFiles/SDL2main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/SDL2/CMakeFiles/SDL2main.dir/depend

