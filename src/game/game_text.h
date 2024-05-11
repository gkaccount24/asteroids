#ifndef GAME_TEXT_H
#define GAME_TEXT_H

#include "game_font.h"

#include <string>

#define GAME_TEXT_STYLE_COUNT 2

enum class game_text_style_index
{
    UNHOVERED = 0,
    HOVERED   = 1
};

struct game_text_style 
{
    SDL_Color ForegroundColor;
    SDL_Color BackgroundColor;

    int Style;
    int Size;
};

struct game_text
{
    game_text_style Styles[GAME_TEXT_STYLE_COUNT];
    game_text_style_index StyleIndex;

    game_font* Font;
    std::string Data;
};

#endif