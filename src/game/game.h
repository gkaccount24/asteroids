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
    /* primary playing states */
    PLAYING,
    PAUSED,
    STOPPED,

    /* initial states */
    CONSTRUCTED,
    SHOWING_MENU
};

struct game_background
{
    game_texture* Texture;
    int XOffset;
    int YOffset;
    size Size;
};

enum class game_error_code
{
    GFX_INITIALIZATION_FAILED     = -100,
    GFX_FAILED_TO_CREATE_WINDOW   = -101,
    GFX_FAILED_TO_CREATE_RENDERER = -102,
    FAILED_TO_LOAD_ASSET          = -103,
    NONE                          = 0
};

class game
{

public:
    game();
    ~game();

public:
    int Run();

private:
    /* ASSET LOADING / MGMT METHODS */
    bool LoadTexture(uint32_t AssetID, std::string TexturePath);
    bool LoadFont(uint32_t FontID, std::string FontPath, int FontSize);
    void LoadAssets();

    /* ERROR STATE MGMT METHODS */
    bool HasErrorState() const;
    void SetErrorState(game_error_code GameLastErrorCode, 
                       std::string GameLastErrorMessage);

    void SetGameState(game_state_id NextState);

    /* INITIALIZATION AND 
       DESTRUCTION METHODS */
    bool InitGfx();
    bool Init();
    void Destroy();

    int Play();

    /* EVENT MGMT METHODS */
    void HandleEvents();

    /* PER FRAME MGMT METHODS */
    void UpdateTimer();
    void UpdateWindowSize();
    void UpdateKeyState();
    void Update(float Dt);

    /* RENDERING METHODS */
    SDL_Texture* CreateTexture(SDL_Surface* Surface);
    void RenderTexture(SDL_Texture* Texture, game_object* Object);
    void RenderTexture(game_texture* Texture, game_object* Object);
    void RenderTexture(SDL_Texture* Texture, SDL_Rect Dest, float Angle = 0.0f);

    void ClearScreen();
    void SwapBuffers();

    /* DRAWING METHODS */
    void DrawMenu();
    void DrawBackground();
    void DrawShip(ship* Ship);
    void DrawObjects();
    void DrawPlayer();

    /* CREATIONAL & DELETE METHODS */
    void DestroyBackground();
    void DestroyPlayer();

    void MakeBackground();
    void MakePlayer();
    ship* MakeShip(uint32_t AssetID, 
                   int ShipX, int ShipY,
                   int ShipW, int ShipH,
                   float BaseSpeed,
                   float MaxSpeed, 
                   bool Save = false);
    
    /* OBJECT MGMT METHODS */
    uint32_t SaveObject(game_object* Object);

    /* EVENT HANDLING Methods */
    void OnConstruct();
    void OnInit();

    void OnStart();
    void OnPause();
    void OnStop();

private:
    inline bool Playing() const { return State == game_state_id::PLAYING; }
    inline bool Paused() const { return State == game_state_id::PAUSED; }
    inline bool Stopped() const { return State == game_state_id::STOPPED; }
    inline bool ShowMenu() const { return State == game_state_id::SHOWING_MENU; }

private:
    /* GRAPHICS POINTERS
       FOR SDL WINDOW & 
       RENDERER */
    SDL_Window*   Window;
    SDL_Renderer* Renderer;

    /* WINDOW DIMENSIONS 
       UPDATED PER FRAME */
    int WindowW;
    int WindowH;

    /* GAME COLLECTIONS FOR 
       ASSETS & OBJECTS */
    asset_map AssetMap;
    object_map ObjectMap;

    /* GAME STATE RELATED DATA MEMBERS */
    game_state_id State;

    /* BACKGROUND DATA MEMBERS */
    game_background* Background;

    /* MAIN PLAYER OBJECT PTR to MEMORY */
    player* Player;

    /* GLOBAL KEYSTATE STUFF
       UPDATES PER FRAME */
    int          GameKeyCount;
    const Uint8* GameKeys;

    /* GLOBAL ERROR STATE */
    game_error_code LastErrorCode;
    std::string LastErrorMessage;

    /* GLOBAL TIMER DATA MEMBERS */
    std::chrono::time_point<std::chrono::system_clock> DtNow;
    std::chrono::time_point<std::chrono::system_clock> DtLast;
    std::chrono::duration<float>                       Dt;
};

#endif