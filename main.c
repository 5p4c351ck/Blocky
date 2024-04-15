#include "grid.h"

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Cellular automata", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, 0);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Set the drawing color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    // Clear the window with black color
    SDL_RenderClear(renderer);

    // Update the window
    SDL_RenderPresent(renderer);


    srand(clock());
    init_grid(grid);
    populate_grid(grid);	
    
    grid[8][11] = 1;
    grid[9][12] = 1;
    grid[10][10] = 1;
    grid[10][11] = 1;
    grid[10][12] = 1;


    // Wait for a key press
    bool quit = false;
    while (!quit) {

   	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    	SDL_RenderClear(renderer);
    	SDL_RenderPresent(renderer);

	print_grid(grid, renderer);
    	SDL_RenderPresent(renderer);

	usleep(90000);

	
	update_grid(grid);

	SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                quit = true;
            }
        }
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
