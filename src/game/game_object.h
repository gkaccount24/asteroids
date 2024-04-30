#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "game_texture.h"
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
    void SetAssetID(uint32_t ObjectTextureID);
    void SetSize(int ObjectW, int ObjectH);
    void SetPosition(float ObjectX, float ObjectY);
    void SetVelocityParams(float ObjectBaseVel,
                           float ObjectMaxVel);
    void Reset();

public: /* GETTERS */
    inline float CurrentSpeed() const { return Speed.Current; }
    inline float MaxSpeed()     const { return Speed.Max;     }
    inline float Rotation()     const { return Angle;         }
    inline float X()            const { return Position.X;    }
    inline float Y()            const { return Position.Y;    }
    inline int W()              const { return Size.W;        }
    inline int H()              const { return Size.H;        }

public: /* ID GETTERS */
    inline uint32_t GetAssetID() const { return AssetID; }
    inline uint32_t GetWorldID() const { return WorldID; }

private:
    uint32_t WorldID;
    uint32_t AssetID;

    vec2d    Position;
    size     Size;
    speed    Speed;

    float    Angle;
};

#endif