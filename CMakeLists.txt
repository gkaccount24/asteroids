cmake_minimum_required(VERSION 3.25.1)
project(asteroids LANGUAGES CXX)

message(NOTICE "setting compiler flags...")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

include_directories(asteroids "/usr/local/include")

find_library(libSDL NAMES SDL3)

if(NOT libSDL)
    message(FATAL_ERROR "failed to find SDL3")
endif()

find_library(libSDLimg NAMES SDL3_image)

if(NOT libSDLimg)
    message(FATAL_ERROR "failed to find SDL3_image")
endif()

find_library(libSDLttf NAMES SDL3_ttf)

if(NOT libSDLttf)
    message(FATAL_ERROR "failed to find SDL3_ttf")
endif()

add_subdirectory(src)

add_executable(asteroids ${SRC})
target_link_libraries(asteroids PRIVATE ${libSDL} ${libSDLimg} ${libSDLttf})