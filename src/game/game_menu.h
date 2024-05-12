#ifndef GAME_MENU_H
#define GAME_MENU_H

#include "game_renderer.h"
#include "game_texture.h"
#include "game_font.h"

#include <string>
#include <vector>
#include <cstdint>

typedef void(*on_click_handler)();

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

class game_menu_option 
{
public:
     game_menu_option();
    ~game_menu_option();

public:
    void Destroy();

private:
    text_style       Styles[TEXT_STYLE_COUNT];
    text_style_index StyleIndex;
    game_texture*    Texture;

    // display text & action handler
    std::string      Text;
    on_click_handler OnClick;

    // graphical position & size
    vec2d            Position;
    size             Size;
};

class game_menu
{
public:
     game_menu();
    ~game_menu();

public:
    void Destroy();

public:
    inline void SetPosition(float X, float Y) { Position.X = X; Position.Y = Y; }
    inline vec2d GetPosition() const          { return Position;                }
    inline void SetSize(int Width, int Height) { Size.Width = Width; Size.Height = Height; }
    inline size GetSize() const                { return Size;                              }
    inline void       SetFont(game_font* MenuFont) { Font = MenuFont; }
    inline game_font* GetFont() const              { return Font;     }

private:
    std::vector<game_menu_option*> Options;

    game_font* Font;
    vec2d      Position;
    size       Size;
};

// game_menu* CreateMenu(std::string FontKey, std::string FontPath, text_style_index StyleIndex, text_style (&Styles)[TEXT_STYLE_COUNT], std::vector<game_menu_option*>& Options);
// void DestroyMenu(game_menu*&);

#endif