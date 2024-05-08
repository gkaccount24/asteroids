#include "game_renderer.h"

SDL_Texture* CreateTexture(SDL_Renderer* Renderer, SDL_Surface* Surface)
{
    SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, Surface);

    return Texture;
}

SDL_Texture* RenderText(SDL_Renderer* Renderer, TTF_Font* Font, SDL_Color Color, std::string Text)
{
    SDL_Surface* Surface = TTF_RenderText_Solid(Font, Text.c_str(), Color);

    SDL_Texture* Texture = nullptr;

    if(Surface)
    {
        Texture = CreateTexture(Surface);

        if(!Texture)
        {
            // logging, failed to alloc 
            // memory for texture
        }

        SDL_FreeSurface(Surface);

        Surface = nullptr;
    }

    return Texture;
}