#include "game_asset_load.h"

static uint32_t AssetID;

game_asset* LoadTexture(SDL_Renderer* Renderer, std::string Path)
{
    if(Path.empty())
    {
        std::cout << "Load Error: path was empty" << std::endl;
        
        return nullptr;
    }

    SDL_Surface* Surface = IMG_Load(Path.c_str());

    if(!Surface)
    {
        std::cout << "Load error: " << IMG_GetError() << std::endl;

        return nullptr;
    }

    SDL_Texture* Texture = CreateTexture(Renderer, Surface);

    if(!Texture)
    {
        std::cout << "Failed to create texture..." << std::endl;
        std::cout << "Error: " << IMG_GetError()   << std::endl;

        return nullptr;
    }

    game_asset* AssetLoaded   = new game_asset   { };
    AssetLoaded->Data.Texture = new game_texture { };

    AssetLoaded->Data.Texture->Position.X  = 0;
    AssetLoaded->Data.Texture->Position.Y  = 0;
    AssetLoaded->Data.Texture->Size.Width  = Surface->w;
    AssetLoaded->Data.Texture->Size.Height = Surface->h;
    AssetLoaded->Data.Texture->Handle      = Texture;

    AssetLoaded->ID   = ++AssetID;
    AssetLoaded->Path = Path;
    AssetLoaded->Type = game_asset_type::TEXTURE;

    SDL_DestroySurface(Surface);
    Surface = nullptr;

    return AssetLoaded;
}

game_asset* LoadFont(int FontStyle, int FontSize, std::string Path)
{
    if(Path.empty())
    {
        std::cout << "Load error: path was empty" << std::endl;
        
        return nullptr;
    }

    TTF_Font* Font = TTF_OpenFont(Path.c_str(), FontSize);

    if(!Font)
    {
        std::cout << "Load error: " << TTF_GetError() << std::endl;

        return nullptr;
    }

    game_asset* AssetLoaded = new game_asset();
    AssetLoaded->Data.Font  = new game_font();

    AssetLoaded->Data.Font->DefaultSize  = FontSize;
    AssetLoaded->Data.Font->DefaultStyle = FontStyle;
    AssetLoaded->Data.Font->Handle       = Font;

    AssetLoaded->ID   = ++AssetID;
    AssetLoaded->Path = Path;
    AssetLoaded->Type = game_asset_type::FONT;

    return AssetLoaded;
}