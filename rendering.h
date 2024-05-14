#ifndef RENDERING_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct SDL_info{
    int windowWidth;
    int windowHeight;
    int xOffset;
    int yOffset; 
    TTF_Font* font;
    SDL_Window* window;
    SDL_Renderer* renderer; 
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Window* textWindow; 
    SDL_Renderer* textRenderer; 
};

void renderText(TTF_Font *font, const char* text, int x, int y, SDL_Renderer *renderer);
int initialization(struct SDL_info *s);
#define RENDERING_H
#endif