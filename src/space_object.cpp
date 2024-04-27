#include "space_object.h"

space_object::space_object():
    TextureID(0),
    XPos(0), YPos(0), 
    Width(0), Height(0),
    Angle(0.0)
{ }

space_object::space_object(uint32_t ObjectTextureID):
    TextureID(ObjectTextureID),
    XPos(0), YPos(0), 
    Width(0), Height(0),
    Angle(0.0)
{ } 

space_object::space_object(uint32_t ObjectTextureID, 
                           int ObjectX, int ObjectY):
    TextureID(ObjectTextureID),
    XPos(ObjectX),
    YPos(ObjectY),
    Width(0), Height(0),
    Angle(0.0)
{ }

space_object::space_object(uint32_t ObjectTextureID, 
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

space_object::space_object(uint32_t ObjectTextureID, 
                           int ObjectX, int ObjectY, 
                           int ObjectWidth, 
                           int ObjectHeight, 
                           double ObjectAngle):
    TextureID(ObjectTextureID),
    XPos(ObjectX),
    YPos(ObjectY),
    Width(ObjectWidth),
    Height(ObjectHeight),
    Angle(ObjectAngle)
{ }

space_object::~space_object()
{
    Reset();
}

void space_object::Reset()
{
    TextureID = 0;
    XPos = 0;
    YPos = 0;
    Width = 0;
    Height = 0;
    Angle = 0.0;
}

void space_object::Copy(const space_object& Right)
{
    TextureID = Right.TextureID;

    XPos = Right.XPos;
    YPos = Right.YPos;

    Width = Right.Width;
    Height = Right.Height;

    Angle = Right.Angle;
}

void space_object::Move(space_object&& Right)
{
    TextureID = Right.TextureID;

    XPos = Right.XPos;
    YPos = Right.YPos;

    Width = Right.Width;
    Height = Right.Height;

    Angle = Right.Angle;

    Right.TextureID = 0;

    Right.XPos = 0;
    Right.YPos = 0;

    Right.Width = 0;
    Right.Height = 0;

    Angle = 0.0;
}

space_object::space_object(const space_object& Right)
{
    Copy(Right);
}

space_object::space_object(space_object&& Right)
{
    Move(std::move(Right));
}

space_object& space_object::operator=(const space_object& Right)
{
    Copy(Right);

    return *this;
}

space_object& space_object::operator=(space_object&& Right)
{
    Move(std::move(Right));

    return *this;
}