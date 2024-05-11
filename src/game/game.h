#ifndef GAME_H
#define GAME_H

#include "game_asset.h"
#include "game_texture.h"
#include "game_font.h"

#include "game_renderer.h"
#include "game_menu.h"
#include "game_object.h"
#include "game_player.h"
#include "game_state.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

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

struct game_object_map
{
    std::unordered_map<uint32_t, game_object*> Entries;
    std::vector<uint32_t> FreeObjectEntries;
};

struct game
{
    SDL_Window* Window;
    SDL_Renderer* Renderer;

    int WindowWidth;
    int WindowHeight;
    int WindowFlags;

    game_state State;

    std::unordered_map<std::string, game_asset*> Assets;
    game_object_map ObjectMap;

    std::vector<game_menu*> Menus;
    game_menu_state_ids ActiveGameMenuID;

    std::vector<game_background*> Backgrounds;
    std::vector<game_player*> Players;

    /* GLOBAL TIMER DATA MEMBERS */
    std::chrono::time_point<std::chrono::system_clock> DtNow;
    std::chrono::time_point<std::chrono::system_clock> DtLast;
    std::chrono::duration<float> Dt;
};

bool InitGame(game* Game);
void DestroyGame(game* Game);
int PlayGame(game* Game);
int RunGame(game* Game);

#endif