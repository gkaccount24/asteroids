#include "game_font.h"

void SetFontStyle(game_font* Font, int Flags, int FontSize, SDL_Color ForegroundColor, SDL_Color BackgroundColor, SDL_Color HoverColor)
{
    Font->Style.Flags = Flags;
    Font->Style.Size = FontSize;

    Font->Style.Colors[(int) font_color_index::FOREGROUND];
    Font->Style.Colors[(int) font_color_index::BACKGROUND];
    Font->Style.Colors[(int) font_color_index::HOVERED];
}

void SetRegularFontStyle(game_font* Font, int FontSize, SDL_Color ForegroundColor, SDL_Color BackgroundColor, SDL_Color HoverColor)
{
    SetFontStyle(Font, TTF_STYLE_NORMAL, FontSize, ForegroundColor, BackgroundColor, HoverColor);
}

void SetItalicsFontStyle(game_font* Font, int FontSize, SDL_Color ForegroundColor, SDL_Color BackgroundColor, SDL_Color HoverColor)
{
    SetFontStyle(Font, TTF_STYLE_ITALIC, FontSize, ForegroundColor, BackgroundColor, HoverColor);
}

void SetBoldFontStyle(game_font* Font, int FontSize, SDL_Color ForegroundColor, SDL_Color BackgroundColor, SDL_Color HoverColor)
{
    SetFontStyle(Font, TTF_STYLE_BOLD, FontSize, ForegroundColor, BackgroundColor, HoverColor);
}

void SetStrikeThruFontStyle(game_font* Font, int FontSize, SDL_Color ForegroundColor, SDL_Color BackgroundColor, SDL_Color HoverColor)
{
    SetFontStyle(Font, TTF_STYLE_STRIKETHROUGH, FontSize, ForegroundColor, BackgroundColor, HoverColor);
}

void SetUnderlineFontStyle(game_font* Font, int FontSize, SDL_Color ForegroundColor, SDL_Color BackgroundColor, SDL_Color HoverColor)
{
    SetFontStyle(Font, TTF_STYLE_UNDERLINE, FontSize, ForegroundColor, BackgroundColor, HoverColor);
}

void DestroyFont(game_font* Font)
{
    if(Font && Font->Data)
    {
        TTF_CloseFont(Font->Data);

        Font->Data = nullptr;
    }
}