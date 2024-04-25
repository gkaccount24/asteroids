#ifndef asset_loader_H
#define asset_loader_H

#include "asset_map.h"
#include "asset.h"
#include "game_texture.h"
#include "game_font.h"
#include "renderer.h"

#include <string>

class asset_loader
{

public:
    asset_loader(renderer& Renderer);
    ~asset_loader();

public:
    bool LoadTexture(uint32_t TextureID, asset_map& AssetMap, std::string TexturePath);
    bool LoadFont(uint32_t FontID, asset_map& AssetMap, std::string FontPath, int FontSize);

private:
    renderer& Renderer;

};

#endif