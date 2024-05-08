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
    uint32_t         Index;
    SDL_Texture*     Texture;
    on_click_handler Handler;
};

struct game_menu
{
    uint32_t                       MenuID;
    game_font*                     Font;
    std::vector<game_menu_option*> Options;
};

void MakeMenu(game_menu* Menu, std::pair<std::string, on_click_handler>* MenuOptions, uint32_t MenuOptionCount);
void AddMenuOption(game_menu* Menu, std::string OptionText, on_click_handler Handler);

#endif