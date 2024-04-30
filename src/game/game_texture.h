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
    inline SDL_Texture* GetData() const { return Data;   }
    inline int W()                const { return Width;  }
    inline int H()                const { return Height; }

private:
    SDL_Texture* Data;
    int          Width;
    int          Height;
};

#endif