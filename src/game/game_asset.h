#ifndef GAME_ASSET_H
#define GAME_ASSET_H

#include "game_texture.h"
#include "game_font.h"

#include <string>
#include <cstdint>

struct game_asset 
{
    uint32_t    ID;
    std::string Path;

    union {
        game_texture* Texture;
        game_font*    Font;
    } Data;
};

void SetAssetPath(std::string Path);

#endif