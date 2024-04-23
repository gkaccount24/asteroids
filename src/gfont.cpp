#include "gfont.h"

gfont::gfont(TTF_Font* FontData, std::string FontPath, int FontSize):
    Data(FontData),
    Path(FontPath),
    Size(FontSize)
{ }

gfont::~gfont()
{
    if(Data)
    {
        TTF_CloseFont(Data);
        Data = nullptr;
    }

    Path.clear();
    Size = 0;
}