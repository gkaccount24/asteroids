#ifndef GAME_MENU_H
#define GAME_MENU_H

#include "game_renderer.h"
#include "game_texture.h"
#include "game_font.h"
#include "game_text.h"

#include <string>
#include <vector>
#include <cstdint>

typedef void(*on_click_handler)();

struct game_menu_option 
{
    game_text*       Text;
    on_click_handler OnClick;
};

struct game_menu
{
    uint32_t                       MenuID;
    std::vector<game_menu_option*> Options;

    // font applies to all menu options
    game_font*  Font;
    vec2d       Position;
    size        Size;
};

game_menu* CreateMenu(text_style_index StyleIndex, text_style (&Styles)[TEXT_STYLE_COUNT], std::vector<std::pair<std::string, on_click_handler>>& Options);
void DestroyMenu(game_menu*&);

#endif