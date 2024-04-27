#include "grid.h"
#include "rendering.h"

static long long iterations = 0;

static int current = 0;
static int next = 1;


int main(int argc, char* argv[]){
	
	initialization();

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

   	SDL_Rect rect = {0, 0, SQUARE_WIDTH, SQUARE_HEIGHT};

    	char iter_text[100];
    	char quit_text[100];
    	sprintf(iter_text, "Iterations: %lld", iterations);
    	sprintf(quit_text, "Press ESC to quit");


    	srand(clock());

    	clear_grid(grid);
    	populate_grid(grid, current);	

    	bool quit = false;
    	while (!quit) {
		usleep(SPEED);
    
		SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
		
		SDL_RenderClear(textRenderer);
		
		sprintf(iter_text, "Iterations: %lld", iterations);//<-
	    	renderText(font, quit_text, 100, 700, textRenderer);
		renderText(font, iter_text, 100, 200, textRenderer);
       		SDL_RenderPresent(textRenderer);

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
    SDL_DestroyWindow(textWindow);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyRenderer(textRenderer);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture); 
    SDL_Quit();
    return 0;
}
