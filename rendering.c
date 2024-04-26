#include "rendering.h"

void renderText(TTF_Font *font, const char* text, int x, int y, SDL_Renderer *renderer){
        int width, height;
        SDL_Color color = {255, 255, 255};    

        SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    
        SDL_Rect Rect = {x, y, width, height};
        TTF_SizeText(font, text, &Rect.w, &Rect.h);
        SDL_RenderCopy(renderer, texture, NULL, &Rect);
        SDL_RenderPresent(renderer);
    
        if(surface) SDL_FreeSurface(surface);
        if(texture) SDL_DestroyTexture(texture);
        return;
}


int initialization(void){
  /* Initialize SDL */ 
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1) {
        SDL_Log("Unable to initialize SDL_ttf: %s", TTF_GetError());
        return 1;
    }
    return 0;
}