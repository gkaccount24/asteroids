#include "renderer.h"

SDL_Texture* renderer::CreateTexture(SDL_Surface* Surface)
{
    SDL_Texture* Texture = nullptr;

    Texture = SDL_CreateTextureFromSurface(Renderer, Surface);

    return Texture;
}

void renderer::DrawObject(SDL_Texture* Texture, space_object* Object)
{
    SDL_Rect Dest 
    {
        Object->GetXPos(),
        Object->GetYPos(),
        Object->GetWidth(),
        Object->GetHeight()
    };

    double Angle = Object->GetAngle();

    SDL_RenderCopyEx(Renderer, Texture, nullptr, 
                     &Dest, Angle, nullptr, 
                     SDL_FLIP_NONE);
}

void renderer::DrawText(TTF_Font* Font, std::string Text)
{

}