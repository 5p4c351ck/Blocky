#include "grid.h"

char grid[GRID_NUM][WIDTH][HEIGHT];

static char under;		
static char above; 
static char right;
static char left;
static char bottom_left;
static char bottom_right; 
static char upper_right;	
static char upper_left;

void clear_grid(char array[GRID_NUM][WIDTH][HEIGHT]){
	for(unsigned int k = 0; k < GRID_NUM; k++){
		for(unsigned int i = 0; i < WIDTH; i++){
			for(unsigned int j = 0; j < HEIGHT; j++){
				array[k][i][j] = 0;
			}
		}	
	}
}

void populate_grid(char array[GRID_NUM][WIDTH][HEIGHT], int current_grid){
	for(unsigned int i = 0; i < WIDTH; i++){
		for(unsigned int j = 0; j < HEIGHT; j++){
			usleep(10);	
		int random_number = rand() % 2;
			array[current_grid][i][j] = random_number;
			}
		}
	return;
}

int print_grid(char array[GRID_NUM][WIDTH][HEIGHT], SDL_Renderer* renderer, SDL_Rect* rect, SDL_Surface* surface, int xOffset, int yOffset, int current_grid){
	int living_cells = 0;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	for(unsigned int i = 0; i < WIDTH; i++){
		for(unsigned int j = 0; j < HEIGHT; j++){
			if(array[current_grid][i][j]){
				rect->x = (i * SQUARE_WIDTH) + xOffset;
				rect->y = (j * SQUARE_HEIGHT) + yOffset;
    				SDL_FillRect(surface, rect, SDL_MapRGB(surface->format, 255, 255, 255));
				living_cells++;
			}
		}
	}
	return living_cells;
}

int check_neighbours(char array[GRID_NUM][WIDTH][HEIGHT], int x, int y, int current_grid){

	int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
                count += grid[current_grid][nx][ny];
            }
        }
    }
    return count;
}

void update_grid(char array[GRID_NUM][WIDTH][HEIGHT], int* current_grid, int* next_grid){
	for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            int neighbors = check_neighbours(array, i, j, (*current_grid));
            if (grid[(*current_grid)][i][j] == 1) {
                if (neighbors < 2 || neighbors > 3) {
                    grid[(*next_grid)][i][j] = 0; /*Cell dies due to underpopulation or overcrowding*/
                } else {
                    grid[(*next_grid)][i][j] = 1; /*Cell survives*/
                }
            } else {
                if (neighbors == 3) {
                    grid[(*next_grid)][i][j] = 1; /*Cell is born*/
                } else {
                    grid[(*next_grid)][i][j] = 0; /*Cell remains dead*/
                }
            }
        }
    }
    int temp = (*current_grid);
    (*current_grid) = (*next_grid);
    (*next_grid) = temp;
}
