#ifndef GAME_TEXT_H
#define GAME_TEXT_H

#include "game_font.h"
#include "game_texture.h"

#include "common.h"

#include <string>

#define TEXT_STYLE_COUNT 2

enum class text_style_index
{
    UNHOVERED = 0,
    HOVERED   = 1
};

struct text_style 
{
    SDL_Color ForegroundColor;
    SDL_Color BackgroundColor;

    int Style;
    int Size;
};

struct game_text
{
    game_texture*    Texture;
    text_style       Style[TEXT_STYLE_COUNT];
    text_style_index StyleIndex;

    // actual text, position, & 
    // (scaled) up size
    std::string StringData;
    vec2d       Position;
    size        Size;
};

#endif