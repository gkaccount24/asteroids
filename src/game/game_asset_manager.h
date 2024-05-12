#ifndef GAME_ASSET_MANAGER_H
#define GAME_ASSET_MANAGER_H

#include "game_asset.h"
#include "game_menu.h"
#include "game_sound.h"
#include "game_font.h"
#include "game_texture.h"

#include <string>

class game_asset_manager
{
public:
     game_asset_manager() = default;
    ~game_asset_manager() = default;

public:
    game_sound* CreateSound(std::string Path);
    game_texture* CreateTexture(std::string Path);
    game_font* CreateFont(std::string Path, int FontStyle, int FontSize);
    game_menu* CreateMenu(std::string Path, std::string FontKey);
};

#endif