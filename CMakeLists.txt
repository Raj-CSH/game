cmake_minimum_required(VERSION 3.10)

project(Game VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(SRC ${PROJECT_SOURCE_DIR}/src)
set(TESTS ${SRC}/tests)
set(SOURCE_FILES
	${SRC}/keyboard.cpp
	${SRC}/log.cpp
	${SRC}/main.cpp
	${SRC}/util.cpp
	${TESTS}/key_test.cpp
	${TESTS}/log_test.cpp
	${TESTS}/run_tests.cpp
	${TESTS}/test.cpp)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

configure_file(config.h.in config.h)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

add_executable(Game ${SOURCE_FILES})

target_link_libraries(Game ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
target_include_directories(Game PUBLIC
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}/include")

