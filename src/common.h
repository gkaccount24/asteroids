#ifndef COMMON_H
#define COMMON_H

enum font_id 
{
    PressStart2P_Regular_9  = 200,
    PressStart2P_Regular_12 = 201,
    PressStart2P_Regular_24 = 202,
    FontNotDefined          = 203,

    Count = 3
};

#define FONT_ID_OFFSET 200

enum texture_id
{
    AsteroidGrey1  = 100,
    AsteroidGrey2  = 101,
    AsteroidBrown1 = 102,
    AsteroidBrown2 = 103,
    FlagLight      = 104,
    FlagDark       = 105,
    Projectile1    = 106,
    Projectile2    = 107,
    Starship       = 108,
    UFO            = 109,

    TextureNotDefined = 110,

    Count = 11
};

#define TEXTURE_ID_OFFSET 100

#endif