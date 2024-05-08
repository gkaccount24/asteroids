#include "game_player.h"

void DestroyPlayer(game_player* Player)
{
    if(Player)
    {
        Player->Name.clear();

        if(Player->Ship)
        {
            delete Player->Ship;

            Player->Ship = nullptr;
        }
    }
}

void AssignShip(game_player* Player, ship* Ship)
{
    if(Ship)
    {
        if(Player->Ship)
        {
            delete Player->Ship;

            Player->Ship = nullptr;
        }

        Player->Ship = Ship;
    }
}