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

void AssignShip(game_player* Player, game_object* Ship)
{
    if(Ship)
    {
        if(Player->Ship)
        {
            if(Player->Ship->Data.Ship)
            {
                delete Player->Ship->Data.Ship;

                Player->Ship->Data.Ship = nullptr;
            }

            delete Player->Ship;

            Player->Ship = nullptr;
        }

        Player->Ship = Ship;
    }
}