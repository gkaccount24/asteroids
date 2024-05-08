#include "game_font.h"

void DestroyFont(game_font* Font)
{
    if(Font && Font->Data)
    {
        TTF_CloseFont(Font->Data);

        Font->Data = nullptr;
    }

    Font->Color = SDL_Color { 0, 0, 0, 0 };
    Font->Size = 0;
}