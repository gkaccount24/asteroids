#ifndef game_object_H
#define game_object_H

#include "../graphics/game_texture.h"
#include "common.h"

#include <cstdint>
#include <utility>

class renderer;

class game_object
{

protected:
    game_object();
    game_object(uint32_t TextureID);
    game_object(uint32_t TextureID, 
                 int ObjectX, 
                 int ObjectY);
    game_object(uint32_t TextureID, 
                 int ObjectX, 
                 int ObjectY, 
                 int ObjectWidth, 
                 int ObjectHeight);
    game_object(uint32_t TextureID, 
                 int ObjectX, 
                 int ObjectY, 
                 int ObjectWidth, 
                 int ObjectHeight, 
                 float ObjectAngle);
public:
    virtual ~game_object();

public:
    void Reset();

    void Accelerate(float Dt);
    void Move(float Cx, float Cy);
    void Rotate(float Value);

private:
    game_object(const game_object& Right) = delete;
    game_object(game_object&& Right) = delete;
    game_object& operator=(const game_object& Right) = delete;
    game_object& operator=(game_object&& Right) = delete;

public:
    uint32_t ID;
    uint32_t TextureID;

    float XPos;
    float YPos;
    int Width;
    int Height;
    float Angle;

    float BaseVel;
    float CurrentVel;
    float MaxVel;
};

#endif