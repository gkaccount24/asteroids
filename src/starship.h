#ifndef STARSHIP_H
#define STARSHIP_H

#include "space_object.h"
#include "game_texture.h"
#include "common.h"

class renderer;

class starship: public space_object
{

public:
    starship();
    starship(int ObjectX, int ObjectY);
    starship(int ObjectX, int ObjectY, int ObjectWidth, int ObjectHeight);
    starship(int ObjectX, int ObjectY, int ObjectWidth, int ObjectHeight, double ObjectAngle);

public:
    virtual ~starship();

public:
    starship(const starship& Right);
    starship(starship&& Right);

    starship& operator=(const starship& Right) = delete;
    starship& operator=(starship&& Right) = delete;

public:
    int Shield;

};

#endif