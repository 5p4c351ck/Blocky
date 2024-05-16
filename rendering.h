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

int initialization(struct SDL_info *s);
void cleanUp(struct SDL_info *s);
void renderText(TTF_Font *font, const char* text, int x, int y, SDL_Renderer *renderer);
void printTexts(TTF_Font *font, SDL_Renderer *renderer, unsigned long del, unsigned long long iter, int l, int d);
void printPausedText(TTF_Font *font, SDL_Renderer *renderer, int windowWidth);
#define RENDERING_H
#endif
