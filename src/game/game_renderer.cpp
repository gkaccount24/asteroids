#include "game_renderer.h"

SDL_Texture* CreateTexture(SDL_Renderer* Renderer, SDL_Surface* Surface)
{
    SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, Surface);

    return Texture;
}

game_texture* RenderText(SDL_Renderer* Renderer, game_font* Font, text_style* Style, std::string Text)
{
    SDL_Color ForegroundColor = Style->ForegroundColor;
    SDL_Color BackgroundColor = Style->BackgroundColor;
    int FontStyle             = Style->Style;
    int FontSize              = Style->Size;

    TTF_SetFontStyle(Font->Handle, FontStyle);
    TTF_SetFontSize(Font->Handle, FontSize);

    SDL_Surface* Surface = TTF_RenderText_Solid(Font->Handle, Text.c_str(), ForegroundColor);

    if(!Surface)
    {
        std::cout << "Render error: " << SDL_GetError() << std::endl;

        return nullptr;
    }
    
    SDL_Texture* Handle = CreateTexture(Renderer, Surface);

    if(!Handle)
    {
        std::cout << "Render error: " << SDL_GetError() << std::endl;

        SDL_DestroySurface(Surface);
        Surface = nullptr;

        return nullptr;
    }

    game_texture* Texture = new game_texture { };

    Texture->Position.X  = 0.0f;
    Texture->Position.Y  = 0.0f;
    Texture->Size.Width  = Surface->w;
    Texture->Size.Height = Surface->h;
    Texture->Handle      = Handle;

    SDL_DestroySurface(Surface);
    Surface = nullptr;

    return Texture;
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