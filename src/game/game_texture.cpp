#include "game_texture.h"

void DestroyTexture(game_texture* Texture)
{
    if(Texture && Texture->Handle)
    {
        SDL_DestroyTexture(Texture->Handle);
        Texture->Handle = nullptr;

        delete Texture;
        Texture = nullptr;
    }
}