#ifndef RENDERING_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


void renderText(TTF_Font *font, const char* text, int x, int y, SDL_Renderer *renderer);
int initialization(void);
#define RENDERING_H
#endif