#include "rendering.h"
#include "grid.h"


void renderText(TTF_Font *font, const char* text, int x, int y, SDL_Renderer *renderer){
        int width, height;
        SDL_Color color = {255, 255, 255};    

        SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    
        SDL_Rect Rect = {x, y, width, height};
        TTF_SizeText(font, text, &Rect.w, &Rect.h);
        SDL_RenderCopy(renderer, texture, NULL, &Rect);
    
        if(surface) SDL_FreeSurface(surface);
        if(texture) SDL_DestroyTexture(texture);
        return;
}


int initialization(struct SDL_info *s){
  /* Initialize SDL */ 
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1) {
        SDL_Log("Unable to initialize SDL_ttf: %s", TTF_GetError());
        return 1;
    }
   
    s->font = TTF_OpenFont("./_decterm.ttf", 20);
    if (!s->font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return 1;
    }

    s->window = SDL_CreateWindow("Fullscreen Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_BORDERLESS);
    if (!s->window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return 1;
    }

    SDL_GetWindowSize(s->window, &s->windowWidth, &s->windowHeight);

    s->xOffset = ((s->windowWidth - (WIDTH * SQUARE_WIDTH)) / 2);
    s->yOffset = ((s->windowHeight - (HEIGHT * SQUARE_HEIGHT)) / 2);

    s->renderer = SDL_CreateRenderer(s->window, -1, SDL_RENDERER_ACCELERATED);
    if (!s->renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(s->window);
        SDL_Quit();
        return 1;
    }

    s->surface = SDL_CreateRGBSurface(0, s->windowWidth, s->windowHeight, 32, 0, 0, 0, 0);
    if (!s->surface) {
        SDL_Log("Failed to create surface: %s", SDL_GetError());
        SDL_DestroyWindow(s->window);
        SDL_DestroyRenderer(s->renderer);
        SDL_Quit();
    return 1;
    }

    s->texture = SDL_CreateTextureFromSurface(s->renderer, s->surface);
    if (!s->texture) {
    SDL_Log("Failed to create texture: %s", SDL_GetError());
        SDL_DestroyWindow(s->window);
        SDL_DestroyRenderer(s->renderer);
    SDL_FreeSurface(s->surface);
        SDL_Quit();
    return 1;
    }

    s->textWindow = SDL_CreateWindow("Stats", 0, 0, 400, 800, 0);
    if (!s->textWindow) {
        SDL_Log("Failed to create text window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    s->textRenderer = SDL_CreateRenderer(s->textWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!s->textRenderer) {
        SDL_Log("Failed to create text renderer: %s", SDL_GetError());
        SDL_DestroyWindow(s->textWindow);
        SDL_Quit();
        return 1;
    }

    return 0;
    }
