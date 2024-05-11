#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>

enum class game_state_id
{
    /* primary playing states */
    PLAYING,
    PAUSED,
    STOPPED,

    /* initial states */
    CONSTRUCTED,
    AT_START_MENU,
    NONE 
};

enum class game_error_code
{
    GFX_INITIALIZATION_FAILED     = -100,
    GFX_FAILED_TO_CREATE_WINDOW   = -101,
    GFX_FAILED_TO_CREATE_RENDERER = -102,
    FAILED_TO_LOAD_ASSET          = -103,
    NONE                          = 0
};

struct game_state
{
    game_state_id LastStateID;
    game_state_id StateID;

    game_error_code LastErrorCode;
    std::string LastErrorMessage;

    float MouseX;
    float MouseY;

    Uint32 MouseButtonState;

    bool LeftMouseButtonPressed;
    bool MiddleMouseButtonPressed;
    bool RightMouseButtonPressed;

    int GameKeyCount;
    const Uint8* GameKeys;

    bool KeyUp;
    bool KeyDown;
};

#endif