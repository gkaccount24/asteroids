#ifndef GAME_H
#define GAME_H

#include "../collections/object_map.h"
#include "game_object.h"
#include "starship.h"
#include "player.h"

#include "asset_loader.h"
#include "../graphics/renderer.h"
#include "../graphics/game_texture.h"
#include "../graphics/game_font.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <chrono>
#include <math.h>

/* GENERIC HELPER MACROS */
#define TRUE 1
#define FALSE 0

/* HELPER MACROS FOR VARIOUS GAME BEHAVIORS */
#define LOGGING_ENABLED TRUE

/* HELPER MACROS FOR SDL FUNCTION RETURN CODES */
#define IsGood(Result)((Result) == 0)

class game
{

public:

    game();
    ~game();

public:
    bool InitSDL();
    int Play();

private:
    void LoadAssets();
    void Destroy();

    float GetDistance(int XPosA, int YPosA, int XPosB, int YPosB);

    void Update(float Dt);
    void UpdatePlayer(float Dt);

    void DrawObjects();
    void DrawPlayer();

    void DestroyPlayer();
    void MakePlayer(int XPos, int YPos, 
                    int Width, int Height);

    starship* MakeShip(int XPos, int YPos, 
                       int Width, int Height, 
                       bool Save = false);

    starship* MakeShip(int XPos, int YPos, 
                       int Width, int Height, 
                       float BaseVelocity,
                       float MaxVelocity,
                       bool Save = false);

private:
    uint32_t SaveObject(game_object* Object);

private:
    SDL_Window* Window;
    renderer Renderer;
    
    player* Player;

    asset_map AssetMap;
    object_map ObjectMap;

    int GameKeyCount;
    const Uint8* GameKeys;

    int MouseX;
    int MouseY;

    bool Playing;
};

#endif