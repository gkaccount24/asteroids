#include "texture.h"

texture::texture(SDL_Texture* TextureData, std::string TexturePath, int TextureWidth, int TextureHeight):
    Data(TextureData),
    Path(TexturePath),
    Width(TextureWidth),
    Height(TextureHeight)
{ }

texture::~texture()
{
    if(Data)
    {
        SDL_DestroyTexture(Data);

        Data = nullptr;
    }

    Path.clear();

    Width = 0;
    Height = 0;
}