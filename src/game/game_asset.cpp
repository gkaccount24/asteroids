#include "game_asset.h"

game_asset* GetAsset(std::unordered_map<std::string, game_asset*>& Assets, std::string Key)
{
    game_asset* Asset = nullptr;

    auto Entry = Assets.find(Key);

    if(Entry != std::end(Assets))
    {
        Asset = Entry->second;
    }

    return Asset;
}

game_texture* GetTexture(std::unordered_map<std::string, game_asset*>& Assets, std::string Key)
{
    game_texture* Texture = nullptr;
    game_asset* Asset = GetAsset(Assets, Key);

    Texture = Asset->Data.Texture;

    return Texture;
}

game_font* GetFont(std::unordered_map<std::string, game_asset*>& Assets, std::string Key)
{
    game_font* Font = nullptr;
    game_asset* Asset = GetAsset(Assets, Key);

    Font = Asset->Data.Font;

    return Font;
}