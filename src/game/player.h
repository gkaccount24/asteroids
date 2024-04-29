#ifndef PLAYER_H
#define PLAYER_H

#include "ship.h"

class player
{

public:
    player();
    ~player();

public:
    void UseShip(ship* PlayerShip);
    void Destroy();

private:
    ship* Ship;
};

#endif