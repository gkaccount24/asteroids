#include "game_texture.h"

game_texture::game_texture()
{
    Handle = nullptr;

    Position.X = 0.0f;
    Position.Y = 0.0f;

    Size.Width = 0;
    Size.Height = 0;

    // parent class
    Type = game_asset_type::TEXTURE;
}

game_texture::~game_texture()
{
    Destroy();
}

bool game_texture::Load(std::string AssetPath, SDL_Renderer* Renderer)
{
    SDL_assert(Renderer);

    if(AssetPath.empty())
    {
        std::cout << "Load Error: path was empty" << std::endl;
        
        return false;
    }

    SDL_Surface* Surface = IMG_Load(AssetPath.c_str());

    if(!Surface)
    {
        std::cout << "Load error: " << IMG_GetError() << std::endl;

        return false;
    }

    SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, Surface);

    if(!Texture)
    {
        std::cout << "Failed to create texture..." << std::endl;
        std::cout << "Error: " << SDL_GetError()   << std::endl;

        return false;
    }

    SDL_DestroySurface(Surface);
    Surface = nullptr;

    Position.X  = 0;
    Position.Y  = 0;

    Size.Width  = Surface->w;
    Size.Height = Surface->h;

    Handle = Texture;
    Path = AssetPath;

    return true;
}

void game_texture::Destroy()
{
    if(Handle)
    {
        SDL_DestroyTexture(Handle);
        Handle = nullptr;
    }
}