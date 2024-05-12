#ifndef GAME_FONT_H
#define GAME_FONT_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <vector>
#include <string>

struct game_font
{
    TTF_Font* Handle;
    int       DefaultStyle;
    int       DefaultSize;
};

void DestroyFont(game_font* Font);

#endif