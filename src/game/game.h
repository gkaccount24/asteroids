#ifndef GAME_H
#define GAME_H

#include "../collections/asset_map.h"
#include "../collections/object_map.h"

#include "game_texture.h"
#include "game_font.h"

#include "ship.h"
#include "game_object.h"
#include "player.h"

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
    void Update(float Dt);

    /* RENDERING METHODS */
    SDL_Texture* CreateTexture(SDL_Surface* Surface);
    void RenderTexture(SDL_Texture* Texture, game_object* Object);
    void RenderTexture(game_texture* Texture, game_object* Object);
    // void RenderText(TTF_Font* Font, std::string Text);

    void ClearScreen();
    void SwapBuffers();

    /* DRAWING METHODS */
    void DrawObjects();
    void DrawPlayer();

    /* CREATIONAL & DELETE METHODS */
    void DestroyPlayer();
    void MakePlayer();
    ship* MakeShip(uint32_t AssetID, 
                   int ShipX, int ShipY,
                   int ShipW, int ShipH,
                   float BaseSpeed,
                   float MaxSpeed, 
                   bool Save = false);
    
    /* GAME STATE MGMT METHODS */
    void SetGameState(game_state_id NextState);

    /* OBJECT MGMT METHODS */
    uint32_t SaveObject(game_object* Object);

private:
    /* GRAPHICS POINTERS
       FOR SDL WINDOW & 
       RENDERER */
    SDL_Window*   Window;
    SDL_Renderer* Renderer;

    /* GAME COLLECTIONS FOR 
       ASSETS & OBJECTS */
    asset_map AssetMap;
    object_map ObjectMap;

    /* GAME STATE RELATED DATA MEMBERS */
    game_state_id State;
    bool          Playing;

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