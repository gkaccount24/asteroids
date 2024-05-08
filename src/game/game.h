#ifndef GAME_H
#define GAME_H

#include "game_asset.h"
#include "game_texture.h"
#include "game_font.h"

#include "game_renderer.h"
#include "game_menu.h"
#include "game_object.h"
#include "game_player.h"
#include "game_state_vars.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <vector>
#include <unordered_map>

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

struct game_background
{
    game_texture* Texture;
    int XOffset;
    int YOffset;
    size Size;
};

struct game
{
    SDL_Window*   Window;
    SDL_Renderer* Renderer;

    int WindowW;
    int WindowH;

    std::unordered_map<std::string, game_asset*> Assets;
    std::unordered_map<uint32_t, game_object*> Object;

    std::vector<game_background*> Backgrounds;
    std::vector<game_player*> Players;

    /* GLOBAL TIMER DATA MEMBERS */
    std::chrono::time_point<std::chrono::system_clock> DtNow;
    std::chrono::time_point<std::chrono::system_clock> DtLast;
    std::chrono::duration<float>                       Dt;
};

// void OnConstruct();
// void OnInit();
// void OnSettings();
// void OnSave();
// void OnQuit();
// void OnLoad();
// void OnExit();
// void OnStart();
// void OnPause();
// void OnStop();

// bool LoadTexture(game* Game, std::string Key, std::string TexturePath);
// bool LoadFont(game* Game, std::string Key, std::string FontPath, int FontSize);
// void LoadAssets(game* Game);

// void MakePauseMenu(game* Game);
// void MakeMainMenu(game* Game);
// bool InitGfx(game* Game);

bool InitGame(game* Game);
void DestroyGame(game* Game);

// void HandleEvents(game* Game);
// void UpdateTimer(game* Game);
// void UpdateWindowSize(game* Game);
// void Update(game* Game, float Dt);

// void ClearScreen();
// void SwapBuffers();

// void DrawBackground();
// void DrawMenu(game_menu* Menu);
// void DrawShip(ship* Ship);
// void DrawObjects();
// void DrawPlayer();

int PlayGame(game* Game);
int RunGame(game* Game);

#endif