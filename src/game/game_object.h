#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "game_texture.h"

#include "common.h"

#include <cstdint>
#include <utility>

enum class game_object_type_id
{
    SHIP
};

struct ship
{

};

ship* MakeShip(game_texture* Texture,
               int ShipX, int ShipY,
               int ShipW, int ShipH,
               float BaseSpeed, 
               float MaxSpeed);

struct game_object
{
    uint32_t            WorldID;
    game_object_type_id TypeID;
    game_texture*       Texture;

    vec2d Position;
    size  Size;
    speed Speed;

    float Angle;

    union {
        ship* Ship;
    } Data;
};

void Rotate(game_object* Object, float Value = 1.0f);
void Accelerate(game_object* Object, float Dt);
void Move(game_object* Object, float Dt);

void SetWorldID(game_object* Object, uint32_t ObjectWorldID);
void AssignType(game_object* Object, game_object_type_id TypeID);
void AssignTexture(game_object* Object, game_texture* Texture);
void SetSize(game_object* Object, int ObjectW, int ObjectH);
void SetPosition(game_object* Object, float ObjectX, float ObjectY);
void SetVelocityParams(game_object* Object, float ObjectBaseVel,
                       float ObjectMaxVel);
void Reset(game_object* Object);

#endif