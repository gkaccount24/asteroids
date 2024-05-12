#ifndef GAME_ASSET_H
#define GAME_ASSET_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>
#include <cstdint>

enum class game_asset_type 
{
    SURFACE = 0,
    TEXTURE = 1,
    FONT    = 2,
    AUDIO   = 3,
    MENU    = 4
};

class game_asset
{
protected:
             game_asset();
    virtual ~game_asset();

public:
    virtual bool Load(std::string Path, SDL_Renderer* Renderer = nullptr) = 0;
    virtual void Destroy()                                                = 0;

public:
    inline void            SetType(game_asset_type AssetType) { Type = AssetType; }
    inline game_asset_type GetType() const                    { return Type;      }
    inline void        SetKey(std::string AssetKey) { Key = AssetKey; }
    inline std::string GetKey() const               { return Key;     }
    inline void        SetPath(std::string AssetPath) { Path = AssetPath; }
    inline std::string GetPath() const                { return Path;      }

protected:
    game_asset_type Type;
    std::string     Key;
    std::string     Path;
};

#endif