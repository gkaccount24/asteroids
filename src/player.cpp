#include "player.h"

player::player():
    Starship(nullptr) 
{ }

player::~player() 
{
    if(Starship)
    {
        delete Starship;

        Starship = nullptr;
    }
}