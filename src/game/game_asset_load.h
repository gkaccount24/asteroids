#ifndef GAME_ASSET_LOAD_H
#define GAME_ASSET_LOAD_H

#include "game_asset.h"
#include "game_font.h"
#include "game_texture.h"
#include "game_renderer.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <vector>
#include <string>
#include <iostream>

game_asset* LoadTexture(SDL_Renderer* Renderer, std::string Path);
game_asset* LoadFont(int FontStyle, int FontSize, std::string Path);

struct asset_info
{
    std::string Key;
    std::string Path;
};

struct asset_load 
{
    game_asset_type Type;
    asset_info      Info;

    union
    {
        // menu_load* MenuLoad;
        
    } Details;
};

#endif