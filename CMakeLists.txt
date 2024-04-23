cmake_minimum_required(VERSION 3.25.1)
project(asteroids LANGUAGES CXX)

message(NOTICE "setting compiler flags...")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

message(NOTICE "setting build and binary directories...")

set(PROJECT_BUILD_DIR ${PROJECT_SOURCE_DIR}/build)
set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_BINARY_DIR ${PROJECT_BINARY_DIR})

list(APPEND CMAKE_FIND_ROOT_PATH "/usr/local")
#list(APPEND CMAKE_FIND_ROOT_PATH "${PROJECT_SOURCE_DIR}/lib/SDL")
#list(APPEND CMAKE_FIND_ROOT_PATH "/usr/lib/")

message(NOTICE "setting library search paths...")
message(NOTICE "finding library: SDL2...")

if(NOT SDL)
    # message(NOTICE "setting audio driver...")
    # set(ENV{SDL_AUDIODRIVER} "pulseaudio")
    find_library(SDL NAMES SDL2 SDL2main 
                    HINTS ${CMAKE_FIND_ROOT_PATH} 
                    PATHS ${CMAKE_FIND_ROOT_PATH} 
                    PATH_SUFFIXES "lib")

    include_directories(asteroids "/usr/local/include")

    if(NOT SDL_ttf)
        # message(NOTICE "setting audio driver...")
        # set(ENV{SDL_AUDIODRIVER} "pulseaudio")
        find_library(SDLttf NAMES SDL2_ttf
                        HINTS ${CMAKE_FIND_ROOT_PATH} 
                        PATHS ${CMAKE_FIND_ROOT_PATH} 
                        PATH_SUFFIXES "lib")
    endif()

    if(NOT SDL_image)
        # message(NOTICE "setting audio driver...")
        # set(ENV{SDL_AUDIODRIVER} "pulseaudio")
        find_library(SDLimg NAMES SDL2_image
                        HINTS ${CMAKE_FIND_ROOT_PATH} 
                        PATHS ${CMAKE_FIND_ROOT_PATH} 
                        PATH_SUFFIXES "lib")
    endif()
endif()



add_subdirectory(src)

add_executable(asteroids ${SRC_FILES})
target_link_libraries(asteroids PRIVATE ${SDL} ${SDLttf} ${SDLimg})