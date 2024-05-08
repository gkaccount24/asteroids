#ifndef GAME_TEXTURE_H
#define GAME_TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <cstdint>

struct game_texture
{
    SDL_Texture* Data;

    int XOffset;
    int YOffset;
    int Width;
    int Height;
};

void DestroyTexture(game_texture* Texture);

#endif