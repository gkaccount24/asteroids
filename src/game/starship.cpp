#include "starship.h"

#define STARSHIP_SHIELD 100

starship::starship():
    Shield(STARSHIP_SHIELD),
    Moving(false),

    game_object(texture_id::Starship)
{ }

starship::starship(int ObjectX, int ObjectY):
    Shield(STARSHIP_SHIELD),
    Moving(false),

    game_object(texture_id::Starship, 
                ObjectX, 
                ObjectY)
{ }

starship::starship(int ObjectX, 
                   int ObjectY, 
                   int ObjectWidth, 
                   int ObjectHeight):
    Shield(STARSHIP_SHIELD),
    Moving(false),

    game_object(texture_id::Starship, 
                ObjectX, 
                ObjectY, 
                ObjectWidth, 
                ObjectHeight)
{ }

starship::starship(int ObjectX, 
                   int ObjectY, 
                   int ObjectWidth, 
                   int ObjectHeight, 
                   float ObjectAngle):

    Shield(STARSHIP_SHIELD),
    Moving(false),

    game_object(texture_id::Starship, 
                ObjectX, 
                ObjectY, 
                ObjectWidth, 
                ObjectHeight, 
                ObjectAngle)
{ }

starship::starship(int ObjectX, int ObjectY, 
                   int ObjectWidth, 
                   int ObjectHeight, 
                   float ObjectAngle,
                   float ShipBaseVel,
                   float ShipMaxVel):

    Shield(STARSHIP_SHIELD),
    Moving(false),

    game_object(texture_id::Starship, 
                ObjectX, 
                ObjectY, 
                ObjectWidth, 
                ObjectHeight, 
                ObjectAngle)
{ }

starship::~starship()
{
    Shield = 0;
}