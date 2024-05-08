#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "game_object.h"

#include <string>
#include <cstdint>

struct game_player
{
    std::string Name;
    ship*       Ship;
};

void UseShip(ship* PlayerShip);
void DestroyPlayer(game_player* Player);

#endif