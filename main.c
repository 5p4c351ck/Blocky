#include "grid.h"
#include "rendering.h"

static unsigned long long iterations = 0;
static int living_cells = 0;
static int dead_cells = 0;
static int current = 0;
static int next = 1;

struct snapshot s;
unsigned long delay = 100;

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

    	SDL_Window* textWindow = SDL_CreateWindow("Stats", 0, 0, 400, 800, 0);
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
    	char delay_text[100];
	char total_text[100]; 
    	char alive_text[100];
    	char dead_text[100];
    	char arrow_text[] = "Press UP/DOWN arrow to control delay";
    	char pause_text[] = "Press SPACE to pause/resume";
    	char paused_text[] = "P A U S E D";
    	char save_text[] = "Press ENTER to save a snapshot and quit";
    	char quit_text[] = "Press ESC to quit without saving a snapshot";
	sprintf(total_text, "Total cells: %d", CELL_NUM);
    	
	
	srand(clock());

    	clear_grid(grid);
    	populate_grid(grid, current);
	copy_grid(grid, s.initial_pattern, current);

    	bool quit = false;
    	bool paused = false;
    	while (!quit) {	
		SDL_Event event;
       		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
                		quit = true;
            		}
			else if (event.type == SDL_KEYDOWN) {
            			if (event.key.keysym.sym == SDLK_ESCAPE) {
                			quit = true;
            			}
				else if (event.key.keysym.sym == SDLK_RETURN) {
							time(&s.time_of_snapshot);
							s.delay = delay;
							s.iterations = iterations;
							copy_grid(grid, s.grid, current);

							char filename[20];
							strftime(filename, sizeof(filename), "%Y-%m-%d", localtime(&s.time_of_snapshot));
    						FILE *file = fopen(filename, "wb");
    						if (file == NULL) {
    						    perror("Error opening snapshot file");
    						    return 1;
    						}
    						if (fwrite(&s, sizeof(struct snapshot), 1, file) != 1) {
    						    perror("Error writing to snapshot file");
    						    fclose(file);
    						    return 1;
    						}
							fclose(file);
                			quit = true;
            			}
				else if (event.key.keysym.sym == SDLK_SPACE) {
            			}else if (event.key.keysym.sym == SDLK_SPACE) {
               				paused = (paused ? false : true);
            			}
				else if (event.key.keysym.sym == SDLK_RETURN) {
               				struct snapshot s;
					s.iterations = iterations;
					s.delay = delay;
					
                			quit = true;
            			}
				else if (event.key.keysym.sym == SDLK_UP) {
               				if (delay > 10) delay -= 10;
            			}
				else if (event.key.keysym.sym == SDLK_DOWN) {
               				if (delay < 500) delay += 10;
            			}			
			}
		}
		if (!paused){	
		SDL_Delay(delay);
    
		SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
		
	        living_cells = print_grid(grid, renderer, &rect, surface, xOffset, yOffset, current);
		dead_cells = (CELL_NUM - living_cells);

		SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);
       		SDL_RenderCopy(renderer, texture, NULL, NULL);
       		SDL_RenderPresent(renderer);

		SDL_RenderClear(textRenderer);
		sprintf(iter_text, "Iterations: %lld", iterations);//<-
		sprintf(delay_text, "Iteration Delay: %ld", delay);//<-
	    	sprintf(alive_text,"Living cells: %d", living_cells);
    		sprintf(dead_text, "Dead   cells: %d", dead_cells);
		renderText(font, iter_text, 30, 200, textRenderer);
		renderText(font, delay_text, 30, 230, textRenderer);
		renderText(font, total_text, 30, 270, textRenderer);
		renderText(font, alive_text, 30, 300, textRenderer);
		renderText(font, dead_text,  30, 330, textRenderer);
	    	renderText(font, arrow_text, 30, 600, textRenderer);
	    	renderText(font, pause_text, 30, 650, textRenderer);
	    	renderText(font, save_text, 30, 700, textRenderer);
	    	renderText(font, quit_text, 30, 750, textRenderer);
		SDL_RenderPresent(textRenderer);

     		update_grid(grid, &current, &next);
       		iterations++;
		}
		else{
	    		renderText(font, paused_text, (windowWidth / 2) - 25, 100, renderer);
			SDL_RenderPresent(renderer);
			SDL_Delay(100);
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
