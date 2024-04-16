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
