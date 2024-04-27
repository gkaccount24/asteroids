#ifndef GAME_H
#define GAME_H

#include "game_texture.h"
#include "game_font.h"
#include "renderer.h"
#include "asset_loader.h"
#include "object_map.h"
#include "space_object.h"
#include "starship.h"
#include "player.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <unordered_map>
#include <string>
#include <math.h>

/* GENERIC HELPER MACROS */
#define TRUE 1
#define FALSE 0

/* HELPER MACROS FOR VARIOUS GAME BEHAVIORS */
#define LOGGING_ENABLED TRUE

/* HELPER MACROS FOR SDL FUNCTION RETURN CODES */
#define IsGood(Result)((Result) == 0)

enum {

};

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

    void Update(double DeltaTime);
    void UpdatePlayer(double DeltaTime);

    void DrawObjects();
    void DrawPlayer();

    void DestroyPlayer();
    void MakePlayer(int XPos, int YPos, 
                    int Width, int Height);

    starship* MakeShip(int XPos, int YPos, 
                       int Width, int Height, 
                       bool Save = false);

private:
    uint32_t SaveObject(space_object* Object);

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