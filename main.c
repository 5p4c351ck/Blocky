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
	
	struct SDL_info sdlInfo;

	initialization(&sdlInfo);


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
            			
               				paused = (paused ? false : true);
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
    
		SDL_FillRect(sdlInfo.surface, NULL, SDL_MapRGB(sdlInfo.surface->format, 0, 0, 0));
		
	        living_cells = print_grid(grid,sdlInfo.renderer, &rect, sdlInfo.surface, sdlInfo.xOffset, sdlInfo.yOffset, current);
		dead_cells = (CELL_NUM - living_cells);

		SDL_UpdateTexture(sdlInfo.texture, NULL, sdlInfo.surface->pixels, sdlInfo.surface->pitch);
       		SDL_RenderCopy(sdlInfo.renderer, sdlInfo.texture, NULL, NULL);
       		SDL_RenderPresent(sdlInfo.renderer);

		SDL_RenderClear(sdlInfo.textRenderer);
		sprintf(iter_text, "Iterations: %lld", iterations);
		sprintf(delay_text, "Iteration Delay: %ld", delay);
	    	sprintf(alive_text,"Living cells: %d", living_cells);
    		sprintf(dead_text, "Dead   cells: %d", dead_cells);
		renderText(sdlInfo.font, iter_text, 30, 200, sdlInfo.textRenderer);
		renderText(sdlInfo.font, delay_text, 30, 230, sdlInfo.textRenderer);
		renderText(sdlInfo.font, total_text, 30, 270, sdlInfo.textRenderer);
		renderText(sdlInfo.font, alive_text, 30, 300, sdlInfo.textRenderer);
		renderText(sdlInfo.font, dead_text,  30, 330, sdlInfo.textRenderer);
	    	renderText(sdlInfo.font, arrow_text, 30, 600, sdlInfo.textRenderer);
	    	renderText(sdlInfo.font, pause_text, 30, 650, sdlInfo.textRenderer);
	    	renderText(sdlInfo.font, save_text, 30, 700, sdlInfo.textRenderer);
	    	renderText(sdlInfo.font, quit_text, 30, 750, sdlInfo.textRenderer);
		SDL_RenderPresent(sdlInfo.textRenderer);

     		update_grid(grid, &current, &next);
       		iterations++;
		}
		else{
	    		renderText(sdlInfo.font, paused_text, (sdlInfo.windowWidth / 2) - 25, 100, sdlInfo.renderer);
			SDL_RenderPresent(sdlInfo.renderer);
			SDL_Delay(100);
		}
    	}

    /* Cleanup */
    SDL_DestroyWindow(sdlInfo.window);
    SDL_DestroyWindow(sdlInfo.textWindow);
    SDL_DestroyRenderer(sdlInfo.renderer);
    SDL_DestroyRenderer(sdlInfo.textRenderer);
    SDL_FreeSurface(sdlInfo.surface);
    SDL_DestroyTexture(sdlInfo.texture); 
    SDL_Quit();
    return 0;
}
