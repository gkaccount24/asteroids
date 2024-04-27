#include "renderer.h"

renderer::renderer():
    Renderer(nullptr)
{

}

renderer::~renderer()
{
    Destroy();
}

bool renderer::Create(SDL_Window* Window)
{
    if(!Window)
    {
        return false;
    }

    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

    if(!Renderer)
    {
        return false;
    }

    return true;
}

void renderer::Destroy()
{
    if(Renderer)
    {
        SDL_DestroyRenderer(Renderer);

        Renderer = nullptr;
    }
}

SDL_Texture* renderer::CreateTexture(SDL_Surface* Surface)
{
    SDL_Texture* Texture = nullptr;

    Texture = SDL_CreateTextureFromSurface(Renderer, Surface);

    return Texture;
}

void renderer::ClearScreen()
{
    Uint8 RValue = 0; // Map.Background.r;
    Uint8 GValue = 0; // Map.Background.g;
    Uint8 BValue = 0; // Map.Background.b;

    Uint8 Opacity = SDL_ALPHA_OPAQUE;

    SDL_SetRenderDrawColor(Renderer, RValue, GValue, BValue, Opacity);
    SDL_RenderClear(Renderer);
}

void renderer::SwapBuffers()
{
    SDL_RenderPresent(Renderer);
}

void renderer::DrawTexture(game_texture* Texture, space_object* Object)
{
    DrawTexture(Texture->Data, Object);
}

void renderer::DrawTexture(SDL_Texture* Texture, space_object* Object)
{
    double Angle = Object->GetAngle();
    
    SDL_Rect Dest 
    {
        Object->GetXPos(),
        Object->GetYPos(),
        Object->GetWidth(),
        Object->GetHeight()
    };

    SDL_RenderCopyEx(Renderer, Texture, nullptr, 
                     &Dest, Angle, nullptr, 
                     SDL_FLIP_NONE);
}

void renderer::DrawText(TTF_Font* Font, std::string Text)
{

}