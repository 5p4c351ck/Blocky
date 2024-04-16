#include "grid.h"

int main(int argc, char* argv[]) {
    // Initialize SDL
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

    int xOffset = ((windowWidth - (width * square_width)) / 2);
    int yOffset = ((windowHeight - (height * square_height)) / 2);

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

    SDL_Rect rect = {0, 0, square_width, square_height};

    srand(clock());
    init_grid(grid);
    populate_grid(grid);	
    
    grid[8][11] = 1;
    grid[9][12] = 1;
    grid[10][10] = 1;
    grid[10][11] = 1;
    grid[10][12] = 1;

    bool quit = false;
    while (!quit) {

    	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
	
	usleep(100000);

	print_grid(grid, renderer, &rect, surface, xOffset, yOffset);
    	
	SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
		
	update_grid(grid);

	SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                quit = true;
            }
        }
    }

    // Cleanup
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture); 
    SDL_Quit();
    return 0;
}
