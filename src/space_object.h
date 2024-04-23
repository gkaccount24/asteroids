#ifndef SPACE_OBJECT_H
#define SPACE_OBJECT_H

#include <utility>

enum class space_object_id
{
    AsteroidGrey1 = 0,
    AsteroidGrey2 = 1,

    AsteroidBrown1 = 2,
    AsteroidBrown2 = 3,

    FlagLight = 4,
    FlagDark = 5,

    Projectile1 = 6,
    Projectile2 = 7,

    Starship   = 8,
    UFO        = 9,

    NotDefined = 10
};

class space_object
{

protected:
    space_object();
    space_object(space_object_id ObjectTypeID);
    space_object(space_object_id ObjectTypeID, int ObjectX, int ObjectY);
    space_object(space_object_id ObjectTypeID, int ObjectX, int ObjectY, int ObjectWidth, int ObjectHeight);
    space_object(space_object_id ObjectTypeID, int ObjectX, int ObjectY, int ObjectWidth, int ObjectHeight, double ObjectAngle);

public:
    virtual ~space_object();

public:
    void Reset();

public:
    space_object(const space_object& Right);
    space_object(space_object&& Right);

    space_object& operator=(const space_object& Right);
    space_object& operator=(space_object&& Right);

public:

    inline space_object_id GetTypeID() const { return TypeID; }

    inline int GetXPos() const { return XPos; }
    inline int GetYPos() const { return YPos; }

    inline int GetWidth() const { return Width; }
    inline int GetHeight() const { return Height; }

private:
    void Copy(const space_object& Right);
    void Move(space_object&& Right);

protected:
    space_object_id TypeID;
    int XPos;
    int YPos;
    int    Width;
    int    Height;
    double Angle;
};

#endif