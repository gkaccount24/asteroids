#ifndef game_texture_H
#define game_texture_H

#include "asset.h"

#include <SDL2/SDL.h>
#include <string>
#include <cstdint>

class game_texture: public asset
{

public:
    game_texture(uint32_t TextureID, 
                 std::string TexturePath, 
                 SDL_Texture* TextureData, 
                 int Width, int Height);

    virtual ~game_texture();

public:

    SDL_Texture* Data;
    int Width;
    int Height;
};

#endif