#ifndef GAME_H
#define GAME_H

#include "game_asset.h"
#include "game_sound.h"
#include "game_texture.h"
#include "game_font.h"
#include "game_menu.h"

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

// struct game_object_map
// {
//     std::unordered_map<uint32_t, game_object*> Entries;
//     std::vector<uint32_t>                      EmptyEntries;
// };

class game 
{
public:
     game();
    ~game();

public:
    bool Init();
    
private:
    bool InitGfx();
    void Destroy();

private:
    game_sound*   CreateSound(std::string Path);
    game_texture* CreateTexture(std::string Path);
    game_font*    CreateFont(std::string Path, int FontStyle, int FontSize);
    game_menu* CreateMenu(game_font* Font);
    bool       CreateMenus();

private:
    void LoadAssets();

private:
    void OnInit();

private:
    SDL_Window* Window;
    SDL_Renderer* Renderer;
    int WindowWidth;
    int WindowHeight;
    int WindowFlags;

    std::unordered_map<std::string, game_asset*> Assets;

    /* GLOBAL TIMER DATA MEMBERS */
    std::chrono::time_point<std::chrono::system_clock> DtNow;
    std::chrono::time_point<std::chrono::system_clock> DtLast;
    std::chrono::duration<float> Dt;
};

// bool InitGame(game* Game);
// void DestroyGame(game* Game);
// int PlayGame(game* Game);
// int RunGame(game* Game);

#endif