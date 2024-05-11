#ifndef GAME_ASSET_H
#define GAME_ASSET_H

#include "game_texture.h"
#include "game_font.h"

#include <unordered_map>
#include <string>
#include <cstdint>

enum class game_asset_type_id
{
    TEXTURE,
    FONT
};

struct game_asset 
{
    uint32_t    ID;
    game_asset_type_id Type;
    std::string Path;

    union 
    {
        game_texture* Texture;
        game_font*    Font;

    } Data;
};

game_texture* GetTexture(std::unordered_map<std::string, game_asset*>& Assets, std::string Key);
game_font* GetFont(std::unordered_map<std::string, game_asset*>& Assets, std::string Key);

#endif