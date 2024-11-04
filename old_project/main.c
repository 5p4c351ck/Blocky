
#include "grid.h"
#include "rendering.h"
#include "options.h"

static unsigned long long iterations = 0;
static int living_cells = 0;
static int dead_cells = 0;
static int current = 0;
static int next = 1;


struct snapshot s;
unsigned long delay = 100;

int main(int argc, char* argv[]){

		struct user_options usrop;
		struct SDL_info sdlInfo;
		
		userOptions(argc, argv, &usrop);
		initialization(&sdlInfo);
		
		SDL_Rect rect = {0, 0, SQUARE_WIDTH, SQUARE_HEIGHT};
			
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
								/*Add buffer overflow check*/
								if(!usrop.fn){
									strftime(usrop.filename, sizeof(usrop.filename), "%Y-%m-%d", localtime(&s.time_of_snapshot));
								}
								FILE *file = fopen(usrop.filename, "wb");
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
					printTexts(sdlInfo.font, sdlInfo.textRenderer, delay, iterations, living_cells, dead_cells);

						update_grid(grid, &current, &next);
						iterations++;
				}
				else{
					printPausedText(sdlInfo.font, sdlInfo.renderer, sdlInfo.windowWidth);
					SDL_Delay(100);
				}
		}

		cleanUp(&sdlInfo);
		return 0;
}
