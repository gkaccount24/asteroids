#ifndef SPACE_OBJECT_H
#define SPACE_OBJECT_H

#include "game_texture.h"
#include "common.h"

#include <cstdint>
#include <utility>

class renderer;

class space_object
{

protected:
    space_object();
    space_object(uint32_t TextureID);
    space_object(uint32_t TextureID, int ObjectX, int ObjectY);
    space_object(uint32_t TextureID, int ObjectX, int ObjectY, int ObjectWidth, int ObjectHeight);
    space_object(uint32_t TextureID, int ObjectX, int ObjectY, int ObjectWidth, int ObjectHeight, double ObjectAngle);

public:
    virtual ~space_object();

public:
    void Reset();

public:
    space_object(const space_object& Right);
    space_object(space_object&& Right);

    space_object& operator=(const space_object& Right);
    space_object& operator=(space_object&& Right);

private:
    void Copy(const space_object& Right);
    void Move(space_object&& Right);

public:
    uint32_t ID;
    uint32_t TextureID;
    int XPos;
    int YPos;
    int    Width;
    int    Height;
    double Angle;
};

#endif