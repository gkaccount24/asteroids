#include "./game/game.h"

#include <iostream>

#undef main

int main() 
{
    game Asteroids { };

    if(!Asteroids.InitSDL())
    {
        std::cout << "failed to initialize game." << std::endl;

        return EXIT_FAILURE;
    }

    Asteroids.Init();

    return Asteroids.Play();
}