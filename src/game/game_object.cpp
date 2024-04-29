#include "game_object.h"

game_object::game_object()
{ }

game_object::~game_object()
{
    Reset();
}

void game_object::Reset()
{
    WorldID = 0; // invalid world id, all id's must be non zero
    AssetID = 0; // invalid asset id, all id's must be non zero

    Geometry.X = 0;
    Geometry.Y = 0;
    Geometry.W = 0;
    Geometry.H = 0;

    Speed.Base    = 0.0f;
    Speed.Current = 0.0f;
    Speed.Max     = 0.0f;

    Angle = 0.0f;
}

void game_object::SetWorldID(uint32_t ObjectWorldID)
{
    if(ObjectWorldID == 0)
    {
        // logging, invalid world id
        // assigned
    }

    WorldID = ObjectWorldID;
}

void game_object::SetTextureID(uint32_t ObjectAssetID)
{
    if(ObjectAssetID == 0)
    {
        // logging, invalid texture id
        // assigned
    }

    AssetID = ObjectAssetID;
}

void game_object::SetSize(int ObjectW, int ObjectH)
{
    Geometry.W = ObjectW;
    Geometry.H = ObjectH;
}

void game_object::SetPosition(float ObjectX, float ObjectY)
{
    Geometry.X = ObjectX;
    Geometry.Y = ObjectY;
}

void game_object::SetVelocityParams(float ObjectBaseSpeed,
                                    float ObjectMaxSpeed)
{
    Speed.Base    = ObjectBaseSpeed;
    Speed.Current = ObjectBaseSpeed;
    Speed.Max     = ObjectMaxSpeed;
}

void game_object::Rotate(float Value)
{
    Angle = Angle - Value;

    if(Angle <= 0.0f)
    {
        Angle = 360.0f;
    }
    else if(Angle >= 360.0f)
    {
        Angle = 0.0f;
    }
}

void game_object::Accelerate(float Dt) 
{
    if(Speed.Current < Speed.Max)
    {
        Speed.Current += Speed.Base * Dt;
    }
} 

void game_object::Move(float Dt) 
{
    Geometry.X += Speed.Current * cosf(TO_RADIANS(Angle)) * Dt;
    Geometry.Y += Speed.Current * sinf(TO_RADIANS(Angle)) * Dt;
}