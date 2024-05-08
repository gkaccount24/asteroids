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
void SetSize(game_object* Object, size Size);
void SetPosition(game_object* Object, vec2d Position);
void SetVelocityParams(game_object* Object, speed Speed);
void Reset(game_object* Object);

game_object* MakeShip(std::unordered_map<std::string, game_asset*>& Assets, vec2d Position, size Size, speed Speed);
// game_object* MakeUFO(std::unordered_map<std::string, game_asset*>& Assets, vec2d Position, size Size, speed Speed);
// game_object* MakeAsteroid(std::unordered_map<std::string, game_asset*>& Assets, vec2d Position, size Size, speed Speed);
// game_object* MakeProjectile(std::unordered_map<std::string, game_asset*>& Assets, vec2d Position, size Size, speed Speed);
// game_object* MakeFlag(std::unordered_map<std::string, game_asset*>& Assets, vec2d Position, size Size, speed Speed);

#endif