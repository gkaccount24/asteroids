#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../graphics/game_texture.h"
#include "common.h"

#include <cstdint>
#include <utility>

class game_object
{

private:
    game_object(const game_object& Right) = delete;
    game_object(game_object&& Right) = delete;
    game_object& operator=(const game_object& Right) = delete;
    game_object& operator=(game_object&& Right) = delete;

protected:
             game_object();
public:
    virtual ~game_object();

public:
    void Rotate(float Value = 1.0f);
    void Accelerate(float Dt);
    void Move(float Dt);

    void SetWorldID(uint32_t ObjectWorldID);
    void SetTextureID(uint32_t ObjectTextureID);
    void SetSize(int ObjectW, int ObjectH);
    void SetPosition(float ObjectX, float ObjectY);
    void SetVelocityParams(float ObjectBaseVel,
                           float ObjectMaxVel);
    void Reset();

public: /* GETTERS */
    inline float CurrentSpeed() const { return Speed.Current; }
    inline float MaxSpeed()     const { return Speed.Max;     }
    inline int X()              const { return Geometry.X;    }
    inline int Y()              const { return Geometry.Y;    }

private:
    uint32_t WorldID;
    uint32_t AssetID;

    geometry Geometry;
    speed    Speed;
    float    Angle;
};

#endif