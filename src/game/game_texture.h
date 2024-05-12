#ifndef GAME_TEXTURE_H
#define GAME_TEXTURE_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "common.h"

#include <string>
#include <cstdint>

struct game_texture
{
    SDL_Texture* Handle;

    // position and size 
    // relative to texture sheet,
    // if it is a texture sheet
    vec2d        Position;
    size         Size;
};

void DestroyTexture(game_texture* Texture);

#endif