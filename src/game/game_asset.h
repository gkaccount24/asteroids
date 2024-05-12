#ifndef GAME_ASSET_H
#define GAME_ASSET_H

#include "game_texture.h"
#include "game_font.h"

#include <unordered_map>
#include <string>
#include <cstdint>

enum class game_asset_type
{
    SURFACE = 0,
    TEXTURE = 1,
    FONT    = 2,
    AUDIO   = 3,
    MENU    = 4
};

struct game_asset 
{
    uint32_t        ID;
    std::string     Key;
    std::string     Path;
    game_asset_type Type;

    union 
    {
        game_texture* Texture;
        game_font*    Font;

    } Data;
};

game_texture* GetTexture(std::unordered_map<std::string, game_asset*>& Assets, std::string Key);
game_font* GetFont(std::unordered_map<std::string, game_asset*>& Assets, std::string Key);

#endif