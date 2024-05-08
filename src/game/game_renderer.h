#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>

SDL_Texture* CreateTexture(SDL_Renderer* Renderer, SDL_Surface* Surface);
SDL_Texture* RenderText(SDL_Renderer* Renderer, TTF_Font* Font, SDL_Color Color, std::string Text);

void ClearScreen(SDL_Renderer* Renderer, SDL_Color Color);
void SwapBuffers(SDL_Renderer* Renderer);

#endif