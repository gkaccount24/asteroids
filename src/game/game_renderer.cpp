#include "game_renderer.h"

SDL_Texture* CreateTexture(SDL_Renderer* Renderer, SDL_Surface* Surface)
{
    SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, Surface);

    return Texture;
}

game_texture* RenderText(SDL_Renderer* Renderer, TTF_Font* Font, SDL_Color Color, std::string Text)
{
    SDL_Surface* Surface = TTF_RenderText_Solid(Font, Text.c_str(), Color);
    game_texture* Texture = nullptr;

    if(!Surface)
    {
        std::cout << "failed to render game text" << std::endl;
        std::cout << "SDL_GetError(): " << SDL_GetError() << std::endl;

        return nullptr;
    }
    
    SDL_Texture* TextureData = nullptr;
    TextureData = CreateTexture(Renderer, Surface);

    if(!TextureData)
    {
        std::cout << "failed to render game text" << std::endl;
        std::cout << "SDL_GetError(): " << SDL_GetError() << std::endl;

        SDL_DestroySurface(Surface);
        Surface = nullptr;

        return nullptr;
    }

    Texture = new game_texture();

    Texture->Position.X = 0.0f;
    Texture->Position.Y = 0.0f;
    Texture->Size.Width = Surface->w;
    Texture->Size.Height = Surface->h;
    Texture->Data = TextureData;

    SDL_DestroySurface(Surface);
    Surface = nullptr;

    return Texture;
}

game_texture* RenderText(SDL_Renderer* Renderer, game_font* Font, std::string Text)
{
    // return RenderText(Renderer, Font->Data, Font->Style.ForegroundColor, Text);

    return nullptr;
}

void DrawText(SDL_Renderer* Renderer)
{

}

void Draw(SDL_Renderer* Renderer, SDL_Texture* Texture, SDL_FRect SourceRECT, SDL_FRect DestRECT, double Angle, SDL_Color Color)
{
    SDL_SetRenderDrawColor(Renderer, Color.r, Color.g, Color.b, Color.a);
    SDL_RenderTextureRotated(Renderer, Texture, &SourceRECT, &DestRECT, Angle, nullptr, SDL_FLIP_NONE);
}

void ClearScreen(SDL_Renderer* Renderer, SDL_Color Color)
{
    SDL_SetRenderDrawColor(Renderer, Color.r, Color.g, Color.b, Color.a);
    SDL_RenderClear(Renderer);
}

void SwapBuffers(SDL_Renderer* Renderer)
{
    SDL_RenderPresent(Renderer);
}