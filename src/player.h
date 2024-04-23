#ifndef PLAYER_H
#define PLAYER_H

#include "starship.h"

class player
{
public:
    player();
    player(starship* PlayerStarship);
    ~player();

private:
    starship* Starship;
};

#endif