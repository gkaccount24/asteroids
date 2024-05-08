#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "game_asset.h"
#include "common.h"

#include <unordered_map>
#include <utility>
#include <cstdint>

enum class game_object_type_id
{
    SHIP,
    UFO,
    ASTEROID,
    PROJECTILE,
    FLAG
};

struct ship       { };
struct ufo        { };
struct asteroid   { };
struct projectile { };
struct flag       { };

ship* MakeShip(vec2d Position, size Size, speed Speed);
ufo* MakeUFO(vec2d Position, size Size, speed Speed);
asteroid* MakeAsteroid(vec2d Position, size Size, speed Speed);
projectile* MakeProjectile(vec2d Position, size Size, speed Speed);
flag* MakeFlag(vec2d Position, size Size, speed Speed);

struct game_object
{
    uint32_t            WorldID;
    game_object_type_id TypeID;
    game_texture*       Texture;

    vec2d Position;
    size  Size;
    speed Speed;

    float Angle;

    union 
    {
        ship*       Ship;
        ufo*        UFO;
        asteroid*   Asteroid;
        projectile* Projectile;
        flag*       Flag;

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