#ifndef GAME_MENU_H
#define GAME_MENU_H

#include "game_state_vars.h"
#include "game_texture.h"
#include "game_font.h"

#include <string>
#include <vector>
#include <cstdint>

typedef void(*on_click_handler)(game_state_vars* StateVars);

struct game_menu_option 
{
    SDL_Texture* Texture;
    uint32_t Index;
    std::string Text;
    on_click_handler Handler;
};

struct game_menu
{
    std::vector<game_menu_option*> Options;
    uint32_t MenuID;
    game_font* Font;
};

#endif