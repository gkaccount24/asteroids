#ifndef STARSHIP_H
#define STARSHIP_H

#include "game_object.h"
#include "common.h"

#include <math.h>

class renderer;

class starship: public game_object
{

public:
    starship();
    starship(int ObjectX, 
             int ObjectY);
    starship(int ObjectX, 
             int ObjectY, 
             int ObjectWidth, 
             int ObjectHeight);
    starship(int ObjectX, 
             int ObjectY, 
             int ObjectWidth, 
             int ObjectHeight, 
             float ObjectAngle);
    starship(int ObjectX, 
             int ObjectY, 
             int ObjectWidth, 
             int ObjectHeight, 
             float ObjectAngle,
             float ShipBaseVel,
             float ShipMaxVel);
public:
    virtual ~starship();

private:
    starship(const starship& Right) = delete;
    starship(starship&& Right) = delete;
    starship& operator=(const starship& Right) = delete;
    starship& operator=(starship&& Right) = delete;

public:
   int Shield;
   bool Moving;
};

#endif