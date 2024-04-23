#ifndef gfont_H
#define gfont_H

#include <SDL2/SDL_ttf.h>

#include <string>

class gfont
{

public:

    gfont(TTF_Font* FontData, std::string FontPath, int FontSize);
    ~gfont();

private:
    TTF_Font*   Data;
    std::string Path;
    int         Size;
};

#endif