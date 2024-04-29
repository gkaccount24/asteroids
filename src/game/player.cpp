#include "player.h"

player::player():
    Ship(nullptr) 
{ }

player::~player() 
{ }

void player::UseShip(ship* PlayerShip)
{
    if(PlayerShip)
    {
        if(Ship)
        {
            delete Ship;

            Ship = nullptr;
        }

        Ship = PlayerShip;
    }
}