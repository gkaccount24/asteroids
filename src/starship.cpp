#include "starship.h"

starship::starship():
    space_object(space_object_id::Starship)
{ }

starship::starship(int ObjectX, int ObjectY, int ObjectWidth, int ObjectHeight, double ObjectAngle):
    space_object(space_object_id::Starship, ObjectX, ObjectY, ObjectWidth, ObjectHeight, ObjectAngle)
{ }

starship::~starship()
{ }

starship::starship(const starship& Right):
    space_object(Right)
{ }

starship::starship(starship&& Right):
    space_object(std::move(Right))
{ }