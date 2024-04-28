#ifndef RENDERER_H
#define RENDERER_H

#include "../game/game_object.h"
#include "game_texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>

class renderer 
{

public:
     renderer();
    ~renderer();

public:
    bool Create(SDL_Window* Window);
    SDL_Texture* CreateTexture(SDL_Surface* Surface);
    void Destroy();

public:
    void ClearScreen();
    void SwapBuffers();

    void DrawTexture(game_texture* Texture, game_object* Object);
    void DrawTexture(SDL_Texture* Texture, game_object* Object);
    void DrawText(TTF_Font* Font, std::string Text);

private:
    SDL_Renderer* Renderer;

};

#endif