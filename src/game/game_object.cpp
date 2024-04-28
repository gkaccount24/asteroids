#include "game_object.h"

game_object::game_object():
    TextureID(0),
    XPos(0), YPos(0), 
    Width(0), Height(0),
    Angle(0.0)
{ }

game_object::game_object(uint32_t ObjectTextureID):
    TextureID(ObjectTextureID),
    XPos(0), YPos(0), 
    Width(0), Height(0),
    Angle(0.0)
{ } 

game_object::game_object(uint32_t ObjectTextureID, 
                           int ObjectX, int ObjectY):
    TextureID(ObjectTextureID),
    XPos(ObjectX),
    YPos(ObjectY),
    Width(0), Height(0),
    Angle(0.0)
{ }

game_object::game_object(uint32_t ObjectTextureID, 
                           int ObjectX, int ObjectY, 
                           int ObjectWidth, 
                           int ObjectHeight):
    TextureID(ObjectTextureID),
    XPos(ObjectX),
    YPos(ObjectY),
    Width(ObjectWidth),
    Height(ObjectHeight),
    Angle(0.0)
{ }

game_object::game_object(uint32_t ObjectTextureID, 
                           int ObjectX, int ObjectY, 
                           int ObjectWidth, 
                           int ObjectHeight, 
                           float ObjectAngle):
    TextureID(ObjectTextureID),
    XPos(ObjectX),
    YPos(ObjectY),
    Width(ObjectWidth),
    Height(ObjectHeight),
    Angle(ObjectAngle)
{ }

game_object::~game_object()
{
    Reset();
}

void game_object::Reset()
{
    TextureID = 0;
    XPos = 0;
    YPos = 0;
    Width = 0;
    Height = 0;
    Angle = 0.0f;
}

void game_object::Accelerate(float Dt) { } 
void game_object::Move(float Cx, float Cy) { }

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