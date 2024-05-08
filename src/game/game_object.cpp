#include "game_object.h"

ship* MakeShip(std::unordered_map<std::string, game_asset*>& Assets, vec2d Position, size Size, speed Speed)
{
    game_object* Object = new game_object { };
    ship* Ship = nullptr;

    if(Object)
    {
        Ship = new ship { };

        if(!Ship)
        {
            // logging, failed to alloc
            // memory for a ship;

            return nullptr;
        }

        Object->Data.Ship = Ship;

        AssignType(Object, game_object_type_id::SHIP);
        AssignTexture(Object, Texture);

        SetPosition(Object, ShipX, ShipY);
        SetSize(Object, ShipW, ShipH);
        SetVelocityParams(Object, BaseSpeed, MaxSpeed);
    }

    return Ship;
}

ufo* MakeUFO(std::unordered_map<std::string, game_asset*>& Assets, vec2d Position, size Size, speed Speed) { return nullptr; }
asteroid* MakeAsteroid(std::unordered_map<std::string, game_asset*>& Assets, vec2d Position, size Size, speed Speed) { return nullptr; }
projectile* MakeProjectile(std::unordered_map<std::string, game_asset*>& Assets, vec2d Position, size Size, speed Speed) { return nullptr; }
flag* MakeFlag(std::unordered_map<std::string, game_asset*>& Assets, vec2d Position, size Size, speed Speed) { return nullptr; }

void Reset(game_object* Object)
{
    Object->WorldID = 0; // invalid world id, all id's must be non zero
    Object->Texture = nullptr; // invalid asset id, all id's must be non zero

    Object->Position.X = 0;
    Object->Position.Y = 0;
    Object->Size.W = 0;
    Object->Size.H = 0;

    Object->Speed.Base    = 0.0f;
    Object->Speed.Current = 0.0f;
    Object->Speed.Max     = 0.0f;

    Object->Angle = 0.0f;
}

void SetWorldID(game_object* Object, uint32_t WorldID)
{
    if(WorldID == 0)
    {
        // logging, invalid world id
        // assigned
    }

    Object->WorldID = WorldID;
}

void AssignType(game_object* Object, game_object_type_id TypeID)
{
    Object->TypeID = TypeID;
}

void AssignTexture(game_object* Object, game_texture* Texture)
{
    if(Texture)
    {
        Object->Texture = Texture;
    }
}

void SetSize(game_object* Object, int ObjectW, int ObjectH)
{
    Object->Size.W = ObjectW;
    Object->Size.H = ObjectH;
}

void SetPosition(game_object* Object, float ObjectX, float ObjectY)
{
    Object->Position.X = ObjectX;
    Object->Position.Y = ObjectY;
}

void SetVelocityParams(game_object* Object, 
                       float BaseSpeed, 
                       float MaxSpeed)
{
    Object->Speed.Base    = BaseSpeed;
    Object->Speed.Current = BaseSpeed;
    Object->Speed.Max     = MaxSpeed;
}

void Rotate(game_object* Object, float Value)
{
    Object->Angle = Object->Angle - Value;

    if(Object->Angle <= 0.0f)
    {
        Object->Angle = 360.0f;
    }
    else if(Object->Angle >= 360.0f)
    {
        Object->Angle = 0.0f;
    }
}

void Accelerate(game_object* Object, float Dt) 
{
    if(Object->Speed.Current < Object->Speed.Max)
    {
        Object->Speed.Current += Object->Speed.Base * Dt;
    }
} 

void Move(game_object* Object, float Dt) 
{
    Object->Position.X += Object->Speed.Current * cosf(TO_RADIANS(Object->Angle)) * Dt;
    Object->Position.Y += Object->Speed.Current * sinf(TO_RADIANS(Object->Angle)) * Dt;
}