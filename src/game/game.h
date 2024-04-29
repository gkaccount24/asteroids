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

enum class game_state_id
{
    PLAYING,
    PAUSED,
    STOPPED
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
    /* ASSET LOADING / MGMT METHODS */
    bool LoadTexture(uint32_t AssetID, std::string TexturePath);
    bool LoadFont(uint32_t FontID, std::string FontPath, int FontSize);
    void LoadAssets();

    /* INITIALIZATION AND 
       DESTRUCTION METHODS */
    void Destroy();

    /* PER FRAME MGMT METHODS */
    void UpdateTimer();

    /* PER FRAME UPDATE METHODS */
    void Update(float Dt);

    /* DRAWING METHODS */
    void DrawObjects();
    void DrawPlayer();

    /* CREATIONAL METHODS */
    void DestroyPlayer();
    void MakePlayer();

    ship* MakeShip(geometry ShipGeometry,
                   float ShipBaseSpeed, 
                   float ShipMaxSpeed, 
                   bool Save = false);
    
    /* GAME STATE MGMT METHODS */
    void SetGameState(game_state_id NextState);
private:
    uint32_t SaveObject(game_object* Object);

private:
    /* GRAPHICS POINTERS
       FOR SDL WINDOW & 
       RENDERER */
    SDL_Window*   Window;
    SDL_Renderer* Renderer;

    // renderer    Renderer;

    /* GAME COLLECTIONS FOR 
       ASSETS & OBJECTS */
    asset_map  AssetMap;
    object_map ObjectMap;

    /* MAIN PLAYER OBJECT PTR to MEMORY */
    player* Player;

    /* GLOBAL KEYSTATE STUFF
       UPDATES PER FRAME */
    int          GameKeyCount;
    const Uint8* GameKeys;

    /* GLOBAL TIMER DATA MEMBERS */
    std::chrono::time_point<std::chrono::system_clock> DtNow;
    std::chrono::time_point<std::chrono::system_clock> DtLast;
    std::chrono::duration<float>                       Dt;
};

#endif