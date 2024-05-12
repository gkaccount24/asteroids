#include "game_font.h"

game_font::game_font()
{
    Handle = nullptr;
    Style = 0;
    Size = 0;

    // parent class
    Type = game_asset_type::FONT;
}

game_font::~game_font()
{
    Destroy();
}

void game_font::Destroy()
{
    if(Handle) 
    {
        TTF_CloseFont(Handle);

        Handle = nullptr;
    }
}

bool game_font::Load(std::string AssetPath, SDL_Renderer* Renderer)
{
    if(AssetPath.empty())
    {
        std::cout << "Load error: path was empty" << std::endl;
        
        return false;
    }

    TTF_Font* Font = TTF_OpenFont(AssetPath.c_str(), Size);

    if(!Font)
    {
        std::cout << "Load error: " << TTF_GetError() << std::endl;

        return false;
    }

    Handle = Font;
    Path = AssetPath;
}