#include "game_text.h"

void DestroyText(game_text*& Text)
{
    if(Text)
    {
        DestroyTexture(Text->Texture);

        delete Text;
        Text = nullptr;
    }
}

