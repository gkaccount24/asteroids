#ifndef GAME_MENU_H
#define GAME_MENU_H

#include "game_renderer.h"
#include "game_texture.h"
#include "game_font.h"
#include "game_text.h"

#include <string>
#include <vector>
#include <cstdint>

typedef void(*on_click_handler)(game_state* GameState);

struct game_menu_option 
{
    game_text*       Text;
    on_click_handler OnClick;
};

struct game_menu
{
    uint32_t                       MenuID;
    std::vector<game_menu_option*> Options;
};

void DestroyMenu(game_menu*& Menu);
game_menu* MakeMenu(SDL_Renderer* Renderer, game_font* Font, std::vector<std::pair<std::string, on_click_handler>>& Options);

#endif