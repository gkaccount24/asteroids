#ifndef GAME_MENU_H
#define GAME_MENU_H

#include "game_state_vars.h"
#include "game_texture.h"
#include "game_font.h"

#include <string>
#include <vector>
#include <cstdint>

struct game_menu_option 
{
    game_texture* Texture;
    uint32_t      Index;
    std::string   Text;
};

struct game_menu
{
    uint32_t                       MenuID;
    game_font*                     Font;
    std::vector<game_menu_option*> Options;
};

#endif