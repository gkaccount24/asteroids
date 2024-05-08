#include "game_texture.h"

void DestroyTextureData(game_texture* Texture)
{
    if(Texture && Texture->Data)
    {
        SDL_DestroyTexture(Texture->Data);

        Texture->Data = nullptr;
    }

    Texture->Width = 0;
    Texture->Height = 0;
}