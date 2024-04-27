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

    virtual void Draw(renderer& Renderer) const = 0;

public:
    space_object(const space_object& Right);
    space_object(space_object&& Right);

    space_object& operator=(const space_object& Right);
    space_object& operator=(space_object&& Right);

public:

    inline uint32_t GetTextureID() const { return TextureID; }

    inline int GetXPos() const { return XPos; }
    inline int GetYPos() const { return YPos; }
    inline int GetWidth() const { return Width; }
    inline int GetHeight() const { return Height; }
    inline double GetAngle() const { return Angle; }

private:
    void Copy(const space_object& Right);
    void Move(space_object&& Right);

protected:
    uint32_t TextureID;
    int XPos;
    int YPos;
    int    Width;
    int    Height;
    double Angle;

    game_texture* Texture;
};

#endif