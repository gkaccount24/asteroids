#include "game_texture.h"

void DestroyTexture(game_texture* Texture)
{
    if(Texture && Texture->Data)
    {
        SDL_DestroyTexture(Texture->Data);

        Texture->Data = nullptr;
    }

    Texture->Size.Width = 0;
    Texture->Size.Height = 0;
}