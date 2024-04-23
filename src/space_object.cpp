#include "space_object.h"

space_object::space_object():
    TypeID(space_object_id::NotDefined),
    XPos(0), YPos(0), 
    Width(0), Height(0),
    Angle(0.0)
{ }

space_object::space_object(space_object_id ObjectTypeID):
    TypeID(ObjectTypeID),
    XPos(0), YPos(0), 
    Width(0), Height(0),
    Angle(0.0)
{ } 

space_object::space_object(space_object_id ObjectTypeID, int ObjectX, int ObjectY):
    TypeID(ObjectTypeID),
    XPos(ObjectX),
    YPos(ObjectY),
    Width(0), Height(0),
    Angle(0.0)
{ }

space_object::space_object(space_object_id ObjectTypeID, int ObjectX, int ObjectY, int ObjectWidth, int ObjectHeight):
    TypeID(ObjectTypeID),
    XPos(ObjectX),
    YPos(ObjectY),
    Width(ObjectWidth),
    Height(ObjectHeight),
    Angle(0.0)
{ }

space_object::space_object(space_object_id ObjectTypeID, int ObjectX, int ObjectY, int ObjectWidth, int ObjectHeight, double ObjectAngle):
    TypeID(ObjectTypeID),
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
    TypeID = space_object_id::NotDefined;
    XPos = 0;
    YPos = 0;
    Width = 0;
    Height = 0;
    Angle = 0.0;
}

void space_object::Copy(const space_object& Right)
{
    TypeID = Right.TypeID;

    XPos = Right.XPos;
    YPos = Right.YPos;

    Width = Right.Width;
    Height = Right.Height;

    Angle = Right.Angle;
}

void space_object::Move(space_object&& Right)
{
    TypeID = Right.TypeID;

    XPos = Right.XPos;
    YPos = Right.YPos;

    Width = Right.Width;
    Height = Right.Height;

    Angle = Right.Angle;

    Right.TypeID = space_object_id::NotDefined;

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