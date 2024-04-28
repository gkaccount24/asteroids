#include "game_texture.h"

game_texture::game_texture(uint32_t TextureID, 
                           std::string TexturePath, 
                           SDL_Texture* TextureData, 
                           int TextureWidth, 
                           int TextureHeight):
    Data(TextureData),
    Width(TextureWidth),
    Height(TextureHeight),

    // base class constructor call
    asset(TextureID, TexturePath)
{ }

game_texture::~game_texture()
{
    if(Data)
    {
        SDL_DestroyTexture(Data);

        Data = nullptr;
    }

    Width = 0;
    Height = 0;
}