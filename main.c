#include "grid.h"

static long long iterations = 0;

static int current = 0;
static int next = 1;

int main(int argc, char* argv[]) {
    /* Initialize SDL */ 
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1) {
        SDL_Log("Unable to initialize SDL_ttf: %s", TTF_GetError());
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("./_decterm.ttf", 20);
    if (!font) {
    	SDL_Log("Failed to load font: %s", TTF_GetError());
    	return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Fullscreen Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_BORDERLESS);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return 1;
    }
    
    int windowWidth;
    int windowHeight;

    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    int xOffset = ((windowWidth - (WIDTH * SQUARE_WIDTH)) / 2);
    int yOffset = ((windowHeight - (HEIGHT * SQUARE_HEIGHT)) / 2);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* surface = SDL_CreateRGBSurface(0, windowWidth, windowHeight, 32, 0, 0, 0, 0);
    if (!surface) {
        SDL_Log("Failed to create surface: %s", SDL_GetError());
        SDL_DestroyWindow(window);
    	SDL_DestroyRenderer(renderer);
        SDL_Quit();
	return 1;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        SDL_DestroyWindow(window);
    	SDL_DestroyRenderer(renderer);
    	SDL_FreeSurface(surface);
        SDL_Quit();
	return 1;
    }













SDL_Window* textWindow = SDL_CreateWindow("Stats", 0, 0, 300, 800, 0);
if (!textWindow) {
    SDL_Log("Failed to create text window: %s", SDL_GetError());
    SDL_Quit();
    return 1;
}

SDL_Renderer* textRenderer = SDL_CreateRenderer(textWindow, -1, SDL_RENDERER_ACCELERATED);
if (!textRenderer) {
    SDL_Log("Failed to create text renderer: %s", SDL_GetError());
    SDL_DestroyWindow(textWindow);
    SDL_Quit();
    return 1;
}


SDL_Color textColor = {255, 255, 255}; // White color
char text[100];
sprintf(text, "Iterations: %lld", iterations);

SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
if (!textSurface) {
    SDL_Log("Failed to render text surface: %s", TTF_GetError());
    return 1;
}

SDL_Texture* textTexture = SDL_CreateTextureFromSurface(textRenderer, textSurface);
if (!textTexture) {
    SDL_Log("Failed to create text texture: %s", SDL_GetError());
    return 1;
}

SDL_Rect textRect = {100, 100, textSurface->w, textSurface->h}; // Adjust position as needed

    



















    SDL_Rect rect = {0, 0, SQUARE_WIDTH, SQUARE_HEIGHT};

    srand(clock());

    clear_grid(grid);
    populate_grid(grid, current);	
    
    grid[0][8][11] = 1;
    grid[0][9][12] = 1;
    grid[0][10][10] = 1;
    grid[0][10][11] = 1;
    grid[0][10][12] = 1;

    bool quit = false;
    while (!quit) {

    	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
	
        usleep(SPEED);

        print_grid(grid, renderer, &rect, surface, xOffset, yOffset, current);
            
        
        
        
        
        
sprintf(text, "Iterations: %lld", iterations);//<-
SDL_RenderClear(textRenderer);
if (textTexture) {
    SDL_DestroyTexture(textTexture);
}
if (textSurface) {
    SDL_FreeSurface(textSurface);
}
TTF_SizeText(font, text, &textRect.w, &textRect.h);
textSurface = TTF_RenderText_Solid(font, text, textColor);
textTexture = SDL_CreateTextureFromSurface(textRenderer, textSurface);
SDL_RenderCopy(textRenderer, textTexture, NULL, &textRect);//<-
SDL_RenderPresent(textRenderer);//<-






        SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
            
        update_grid(grid, &current, &next);

        
        iterations++;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                quit = true;
            }
        }
    }

    /* Cleanup */
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture); 
    SDL_Quit();
    return 0;
}
