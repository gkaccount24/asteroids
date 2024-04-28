#include "game_font.h"

game_font::game_font(uint32_t FontID, 
                     std::string FontPath, 
                     TTF_Font* FontData, 
                     int FontSize):
    Data(FontData),
    Size(FontSize),

    // base class constructor call
    asset(FontID, FontPath)
{ }

game_font::~game_font()
{
    if(Data)
    {
        TTF_CloseFont(Data);
        Data = nullptr;
    }

    Size = 0;
}