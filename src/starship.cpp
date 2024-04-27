#include "starship.h"

#include "renderer.h"

#define STARSHIP_SHIELD 100

starship::starship():
    Shield(STARSHIP_SHIELD),

    space_object(texture_id::Starship)
{ }

starship::starship(int ObjectX, int ObjectY):
    Shield(STARSHIP_SHIELD),

    space_object(texture_id::Starship, ObjectX, ObjectY)
{ }

starship::starship(int ObjectX, int ObjectY, int ObjectWidth, int ObjectHeight):
    Shield(STARSHIP_SHIELD),

    space_object(texture_id::Starship, ObjectX, ObjectY, ObjectWidth, ObjectHeight)
{ }

starship::starship(int ObjectX, int ObjectY, int ObjectWidth, int ObjectHeight, double ObjectAngle):
    Shield(STARSHIP_SHIELD),

    space_object(texture_id::Starship, ObjectX, ObjectY, ObjectWidth, ObjectHeight, ObjectAngle)
{ }

starship::~starship()
{
    Shield = 0;
}

starship::starship(const starship& Right):
    space_object(Right)
{
    Shield = Right.Shield;
}

starship::starship(starship&& Right):
    space_object(std::move(Right))
{
    Shield = Right.Shield;

    Right.Shield = 0;
}

void starship::Draw(renderer& Renderer) const
{
    Renderer.DrawTexture(Texture->GetTextureData(), Texture->GetTextureRect(), Angle);
}