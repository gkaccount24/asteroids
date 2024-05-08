#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>

SDL_Texture* CreateTexture(SDL_Surface* Surface);
SDL_Texture* CreateTexture(TTF_Font* Font, std::string Text);

#endif