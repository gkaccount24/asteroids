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

enum class menu_text_style_index
{
    UNHOVERED = 0,
    HOVERED   = 1
};

struct menu_text_style 
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

public: 
    void SetStyle(menu_text_style_index OptionStyleIndex, menu_text_style(& OptionStyles)[2]);

public:
    inline void SetText(std::string OptionText) { Text = OptionText; }
    inline std::string GetText() const { return Text; }
    inline void SetClickHandler(on_click_handler ClickHandler) { OnClick = ClickHandler; }
    inline void RunClickHandler() const { OnClick(); }
    inline void SetPosition(float X, float Y) { Position.X = X; Position.Y = Y; }
    inline vec2d GetPosition() const { return Position; }
    inline void SetSize(int Width, int Height) { Size.Width = Width; Size.Height = Height; }
    inline size GetSize() const { return Size; }
 
private:
    menu_text_style       Styles[2];
    menu_text_style_index StyleIndex;
    game_texture*         Texture;

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
    void AddOption(std::string OptionText, on_click_handler Handler);

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

#endif