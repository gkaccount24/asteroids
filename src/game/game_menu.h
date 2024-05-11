#ifndef GAME_MENU_H
#define GAME_MENU_H

#include "game_renderer.h"
#include "game_state.h"
#include "game_texture.h"
#include "game_font.h"

#include <string>
#include <vector>
#include <cstdint>

enum class game_menu_state_ids 
{
    AT_START_MENU = 0,
    PAUSED        = 1
};

typedef void(*on_click_handler)(game_state* GameState);

struct game_menu_option 
{
    uint32_t Index;
    std::string Text;
    on_click_handler Handler;

    // graphical data
    game_texture* Texture;
    vec2d Position;
    size Size;

    font_color_index ColorIndex;
};

struct game_menu
{
    uint32_t MenuID;
    game_font* Font;
    std::vector<game_menu_option*> Options;

    // graphical data
    vec2d Position;
    size Size;
};

void DestroyMenu(game_menu*& Menu);
game_menu* MakeMenu(SDL_Renderer* Renderer, game_font* Font, std::vector<std::pair<std::string, on_click_handler>>& Options);

#endif