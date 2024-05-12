#ifndef GAME_TEXTURE_H
#define GAME_TEXTURE_H

#include "game_asset.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "common.h"

#include <iostream>
#include <string>
#include <cstdint>

class game_texture: public game_asset
{
public:
             game_texture();
    virtual ~game_texture();

public:
    virtual bool Load(std::string AssetPath, SDL_Renderer* Renderer = nullptr);
    virtual void Destroy();

private:
    SDL_Texture* Handle;

    // position and size 
    // relative to texture sheet,
    // if it is a texture sheet
    vec2d        Position;
    size         Size;
};

#endif