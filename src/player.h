#ifndef PLAYER_H
#define PLAYER_H

#include "starship.h"

enum player_state_id
{
    IDLE,
    MOVING,
};

class player_state 
{

};

class player
{

public:
    player();
    ~player();

public:
    void Destroy();

public:
    starship* Starship;

};

#endif