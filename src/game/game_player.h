#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "game_object.h"

#include <string>
#include <cstdint>

struct game_player
{
    std::string Name;
    game_object* Ship;
};

void AssignShip(game_player* Player, game_object* PlayerShip);
void DestroyPlayer(game_player* Player);

#endif