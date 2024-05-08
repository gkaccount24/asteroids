#ifndef GAME_FONT_H
#define GAME_FONT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>

struct game_font
{
    TTF_Font*   Data;

    SDL_Color   Color;
    int         Size;
};

void DestroyFont(game_font* Font);

#endif