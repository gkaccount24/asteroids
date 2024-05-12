#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "game_texture.h"
#include "game_font.h"
#include "game_text.h"

#include <string>
#include <iostream>

SDL_Texture* CreateTexture(SDL_Renderer* Renderer, SDL_Surface* Surface);
game_texture* RenderText(SDL_Renderer* Renderer, game_font* Font, text_style_index StyleIndex, text_style (&Styles)[TEXT_STYLE_COUNT], std::string Text);

void ClearScreen(SDL_Renderer* Renderer, SDL_Color Color);
void SwapBuffers(SDL_Renderer* Renderer);

#endif