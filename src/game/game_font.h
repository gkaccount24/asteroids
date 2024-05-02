#ifndef gfont_H
#define gfont_H

#include "asset.h"

#include <SDL2/SDL_ttf.h>
#include <string>

class game_font: public asset
{

public:
    game_font(uint32_t FontID, 
              std::string FontPath, 
              TTF_Font* FontData, 
              int FontSize);

    virtual ~game_font();

public:
    TTF_Font*   Data;
    SDL_Color   Color;
    int         Size;
};

#endif