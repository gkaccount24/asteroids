#ifndef GAME_STATE_VARS_H
#define GAME_STATE_VARS_H

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

struct game_state_vars
{
    game_state_id LastState;
    game_state_id State;
};

void OnGameInit(game_state_vars* StateVars);
void OnGameLoad(game_state_vars* StateVars);
void OnGameStart(game_state_vars* StateVars);

#endif