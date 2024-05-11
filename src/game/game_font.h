#ifndef GAME_FONT_H
#define GAME_FONT_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>

enum class font_color_index
{
    FOREGROUND = 0,
    BACKGROUND = 1,
    HOVERED    = 2
};

struct game_font_style
{
    int       Flags;
    int       Size;
    SDL_Color Colors[3];
};

struct game_font
{
    TTF_Font*       Data;
    game_font_style Style;
};

void SetRegularFontStyle(game_font* Font, int FontSize, SDL_Color ForegroundColor, SDL_Color BackgroundColor, SDL_Color HoverColor);
void SetItalicsFontStyle(game_font* Font, int FontSize, SDL_Color ForegroundColor, SDL_Color BackgroundColor, SDL_Color HoverColor);
void SetBoldFontStyle(game_font* Font, int FontSize, SDL_Color ForegroundColor, SDL_Color BackgroundColor, SDL_Color HoverColor);
void SetStrikeThruFontStyle(game_font* Font, int FontSize, SDL_Color ForegroundColor, SDL_Color BackgroundColor, SDL_Color HoverColor);
void SetUnderlineFontStyle(game_font* Font, int FontSize, SDL_Color ForegroundColor, SDL_Color BackgroundColor, SDL_Color HoverColor);

void DestroyFont(game_font* Font);

#endif