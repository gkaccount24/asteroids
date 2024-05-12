#ifndef GAME_FONT_H
#define GAME_FONT_H

#include "game_asset.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <vector>
#include <string>
#include <iostream>

class game_font: public game_asset 
{
public:
             game_font();
    virtual ~game_font();

public:
    virtual bool Load(std::string Path, SDL_Renderer* Renderer = nullptr);
    virtual void Destroy();

public:
    inline void SetStyle(int FontStyle) { Style = FontStyle; }
    inline int  GetStyle() const        { return Style;      }
    inline void SetSize(int FontSize) { Size = FontSize; }
    inline int  GetSize() const       { return Size;     }

private:
    TTF_Font* Handle;
    int       Style;
    int       Size;
};

#endif