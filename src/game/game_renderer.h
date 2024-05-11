#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "game_texture.h"
#include "game_font.h"

#include <string>
#include <iostream>

SDL_Texture* CreateTexture(SDL_Renderer* Renderer, SDL_Surface* Surface);
game_texture* RenderText(SDL_Renderer* Renderer, TTF_Font* Font, SDL_Color Color, std::string Text);
game_texture* RenderText(SDL_Renderer* Renderer, game_font* Font, std::string Text);

void Draw(SDL_Renderer* Renderer, SDL_Texture* Texture, SDL_FRect SourceRECT, SDL_FRect DestRECT, double Angle, SDL_Color Color);

void ClearScreen(SDL_Renderer* Renderer, SDL_Color Color);
void SwapBuffers(SDL_Renderer* Renderer);

#endif