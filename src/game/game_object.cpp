#include "game_object.h"

game_object* MakeShip(std::unordered_map<std::string, game_asset*>& Assets, vec2d Position, size Size, speed Speed)
{
    game_object* Object = new game_object { };

    if(Object)
    {
        ship* Ship = new ship { };

        if(!Ship)
        {
            // logging, failed to alloc
            // memory for a ship;

            return nullptr;
        }

        Object->Data.Ship = Ship;

        AssignType(Object, game_object_type_id::SHIP);

        game_texture* Texture = GetTexture(Assets, "Texture_Starship");
        AssignTexture(Object, Texture);

        SetVelocityParams(Object, Speed);
        SetPosition(Object, Position);
        SetSize(Object, Size);
    }

    return Object;
}

// game_object* MakeUFO(std::unordered_map<std::string, game_asset*>& Assets, vec2d Position, size Size, speed Speed) { return nullptr; }
// game_object* MakeAsteroid(std::unordered_map<std::string, game_asset*>& Assets, vec2d Position, size Size, speed Speed) { return nullptr; }
// game_object* MakeProjectile(std::unordered_map<std::string, game_asset*>& Assets, vec2d Position, size Size, speed Speed) { return nullptr; }
// game_object* MakeFlag(std::unordered_map<std::string, game_asset*>& Assets, vec2d Position, size Size, speed Speed) { return nullptr; }

void Reset(game_object* Object)
{
    Object->WorldID = 0; // invalid world id, all id's must be non zero
    Object->Texture = nullptr; // invalid asset id, all id's must be non zero

    Object->Position.X = 0;
    Object->Position.Y = 0;
    Object->Size.W = 0;
    Object->Size.H = 0;

    Object->Speed.Base = 0.0f;
    Object->Speed.Current = 0.0f;
    Object->Speed.Max = 0.0f;

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

void SetSize(game_object* Object, size Size)
{
    Object->Size.W = Size.W;
    Object->Size.H = Size.H;
}

void SetPosition(game_object* Object, vec2d Position)
{
    Object->Position.X = Position.X;
    Object->Position.Y = Position.Y;
}

void SetVelocityParams(game_object* Object, speed Speed)
{
    Object->Speed.Base    = Speed.Base;
    Object->Speed.Current = Speed.Base;
    Object->Speed.Max     = Speed.Max;
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