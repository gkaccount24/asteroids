#include "game_asset_manager.h"

game_sound* game_asset_manager::CreateSound(std::string Path) 
{
    game_sound* Sound = new game_sound();

    return Sound;
}

game_texture* game_asset_manager::CreateTexture(std::string Path) 
{
    game_texture* Texture = new game_texture();

    Texture->SetType(game_asset_type::TEXTURE);
    Texture->SetPath(Path);

    return Texture;
}

game_font* game_asset_manager::CreateFont(std::string Path, int FontStyle, int FontSize)
{
    game_font* Font = new game_font();

    Font->SetStyle(FontStyle);
    Font->SetSize(FontSize);

    Font->SetType(game_asset_type::FONT);
    Font->SetPath(Path);

    return Font;
}