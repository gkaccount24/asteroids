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

public: /* GETTERS */
    inline ship*       GetShip() const { return Ship;         }
    inline const char* GetName() const { return Name.c_str(); }

private:
    ship*       Ship;
    std::string Name;
};

#endif