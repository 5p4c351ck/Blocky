#include "rendering.h"
#include "grid.h"

char iter_text[100];
char delay_text[100];
char total_text[100]; 
char alive_text[100];
char dead_text[100];
char arrow_text[] = "Press UP/DOWN arrow to control delay";
char pause_text[] = "Press SPACE to pause/resume";
char paused_text[] = "P A U S E D";
char save_text[] = "Press ENTER to save a snapshot and quit";
char quit_text[] = "Press ESC to quit without saving a snapshot";



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


void printTexts(TTF_Font *font, SDL_Renderer *renderer, unsigned long del, unsigned long long iter, int l, int d){
        SDL_RenderClear(renderer);
		sprintf(iter_text, "Iterations: %lld", iter);
		sprintf(delay_text, "Iteration Delay: %ld", del);
	    sprintf(alive_text,"Living cells: %d", l);
    	sprintf(dead_text, "Dead   cells: %d", d);
        sprintf(total_text, "Total cells: %d", CELL_NUM);
		renderText(font, iter_text, 30, 200, renderer);
		renderText(font, delay_text, 30, 230, renderer);
		renderText(font, total_text, 30, 270, renderer);
		renderText(font, alive_text, 30, 300, renderer);
		renderText(font, dead_text,  30, 330, renderer);
	    renderText(font, arrow_text, 30, 600, renderer);
	    renderText(font, pause_text, 30, 650, renderer);
	    renderText(font, save_text, 30, 700, renderer);
	    renderText(font, quit_text, 30, 750, renderer);
		SDL_RenderPresent(renderer);
}

void printPausedText(TTF_Font *font, SDL_Renderer *renderer, int windowWidth){
	renderText(font, paused_text, (windowWidth / 2) - 25, 100, renderer);
    SDL_RenderPresent(renderer);
}
