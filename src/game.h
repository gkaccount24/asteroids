#ifndef GAME_H
#define GAME_H

#include "game_texture.h"
#include "game_font.h"
#include "renderer.h"
#include "asset_loader.h"
#include "slot_map.h"
#include "space_object.h"
#include "starship.h"
#include "player.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <unordered_map>
#include <string>

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
    void DestroyAssets();

    void DrawObjects();

private:
    SDL_Window* Window;
    renderer Renderer;
    player Player;

    asset_map              AssetMap;
    slot_map<space_object> ObjectMap;
};

#endif