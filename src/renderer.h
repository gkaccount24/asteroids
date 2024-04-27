#ifndef RENDERER_H
#define RENDERER_H

#include "asset_map.h"
#include "space_object.h"

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
    void Destroy();
    SDL_Texture* CreateTexture(SDL_Surface* Surface);

public:
    void ClearScreen();
    void SwapBuffers();

    void DrawObject(SDL_Texture* Texture, space_object* Object);
    void DrawText(TTF_Font* Font, std::string Text);

private:
    SDL_Renderer* Renderer;

};

#endif