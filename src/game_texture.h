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
    ~game_texture();

public:
    inline SDL_Texture* GetTextureData() const { return Data; }
    inline SDL_Rect GetTextureRect() const { return Rect; }

private:
    SDL_Texture* Data;
    SDL_Rect Rect;
    int Width;
    int Height;
};

#endif