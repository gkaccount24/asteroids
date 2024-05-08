#ifndef GAME_STATE_VARS_H
#define GAME_STATE_VARS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>

enum class game_state_id
{
    /* primary playing states */
    PLAYING,
    PAUSED,
    STOPPED,

    /* initial states */
    CONSTRUCTED,
    AT_START_MENU
};

enum class game_error_code
{
    GFX_INITIALIZATION_FAILED     = -100,
    GFX_FAILED_TO_CREATE_WINDOW   = -101,
    GFX_FAILED_TO_CREATE_RENDERER = -102,
    FAILED_TO_LOAD_ASSET          = -103,
    NONE                          = 0
};

struct game_state_vars
{
    game_state_id LastState;
    game_state_id State;

    game_error_code LastErrorCode;
    std::string     LastErrorMessage;

    int          GameKeyCount;
    const Uint8* GameKeys;
};

#endif