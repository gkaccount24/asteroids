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

using menu_option_list = std::vector<std::pair<std::string, on_click_handler>>;
using menu_list = std::vector<menu_option_list>;
using menu_font_list = std::vector<std::pair<std::string, std::string>>;

struct game_menu_file
{
    menu_text_style_index StyleIndex;
    menu_text_style Styles[2];
    // THESE VECTORS MUST MATCH IN SIZE
    menu_font_list Fonts;
    menu_list      Menus;
};

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
    game_sound* CreateSound(std::string Key, std::string Path);
    game_texture* CreateTexture(std::string Key, std::string Path);
    game_font* CreateFont(std::string Key, std::string Path, int FontStyle, int FontSize);
    game_menu* CreateMenu(game_font* Font, menu_text_style_index StyleIndex, menu_text_style(& Styles)[2], menu_option_list& Options);

private:
    game_texture* RenderMenuText(game_font* Font, std::string Text);

private:
    bool LoadMenus(game_menu_file* MenuFile);
    void PrepareForAssetLoad();
    void LoadAssets();

private:
    void OnInit();

private:
    SDL_Window* Window;
    SDL_Renderer* Renderer;
    int WindowWidth;
    int WindowHeight;
    int WindowFlags;

    std::vector<game_menu*> Menus;

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