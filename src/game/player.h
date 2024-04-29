#ifndef PLAYER_H
#define PLAYER_H

#include "ship.h"

#include <string>
#include <cstdint>

class player
{

public:
    player();
    ~player();

public:
    void UseShip(ship* PlayerShip);
    void Destroy();

private:
    ship*       Ship;
    std::string Name;
};

#endif