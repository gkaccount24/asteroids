#include "asset_loader.h"

asset_loader::asset_loader(renderer& GameRenderer):
    Renderer(GameRenderer)
{ }

asset_loader::~asset_loader()
{ }

bool asset_loader::LoadTexture(uint32_t TextureID, asset_map& AssetMap, std::string TexturePath)
{
    if(!TexturePath.empty())
    {
        SDL_Surface* Surface = nullptr;

        Surface = IMG_Load(TexturePath.c_str());

        if(Surface)
        {
            SDL_Texture* TextureData = nullptr;

            TextureData = Renderer.CreateTexture(Surface);

            if(!TextureData)
            {
                std::cout << "failed to load texture: " << TexturePath << std::endl;;
                std::cout << "IMG_GetError(): " << IMG_GetError() << std::endl;

                return false;
            }

            game_texture* Texture = new game_texture(TextureID, TexturePath, 
                                                     TextureData, Surface->w, 
                                                     Surface->h);
            AssetMap.Add(TextureID, Texture);                

            SDL_FreeSurface(Surface);
            Surface = nullptr;

            return true;
        }
    }

    return false;
}

bool asset_loader::LoadFont(uint32_t FontID, asset_map& AssetMap, std::string FontPath, int FontSize)
{
    if(!FontPath.empty() && FontSize > 0)
    {
        TTF_Font* FontData = nullptr;

        FontData = TTF_OpenFont(FontPath.c_str(), FontSize);

        if(!FontData)
        {
            std::cout << "failed to load font: " << FontPath << std::endl;;
            std::cout << "TTF_GetError(): " << TTF_GetError() << std::endl;

            return false;
        }

        game_font* Font = new game_font(FontID, FontPath, 
                                        FontData, FontSize);
        AssetMap.Add(FontID, Font);

        return true;
    }

    return false;
}