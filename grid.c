#include "grid.h"

char grid[width][height];

static char under;		
static char above; 
static char right;
static char left;
static char bottom_left;
static char bottom_right; 
static char upper_right;	
static char upper_left;

void init_grid(char array[width][height]){
	for(unsigned int i = 0; i < width; i++){
		for(unsigned int j = 0; j < height; j++){
			array[i][j] = 0;
		}
	}	
}

void populate_grid(char array[width][height]){
	for(unsigned int i = 0; i < width; i++){
		for(unsigned int j = 0; j < height; j++){
			usleep(10);	
		int random_number = rand() % 2;
			array[i][j] = random_number;
			}
		}
	return;
}

void print_grid(char array[width][height], SDL_Renderer* renderer, SDL_Rect* rect, SDL_Surface* surface, int xOffset, int yOffset){

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	for(unsigned int i = 0; i < width; i++){
		for(unsigned int j = 0; j < height; j++){
			if(array[i][j]){
				rect->x = (i * square_width) + xOffset;
				rect->y = (j * square_height) + yOffset;
    				SDL_FillRect(surface, rect, SDL_MapRGB(surface->format, 255, 255, 255));
			}
		}
	}
	return;
}

void check_neighbours(char *cell, char *newcell, int i, int j){
	
	unsigned int neighbours = 0;

	if(i < width){
		under = *(cell + height);
		if(under){neighbours++;}
	}
	if(i > 0){
		above = *(cell - height);
		if(above){neighbours++;}
	}
	if(j < height){
		right = *(cell + 1);
		if(right){neighbours++;}
	}
	if(j > 0){
		left = *(cell - 1);
		if(left){neighbours++;}
	}
	if(i < width && j > 0){
		bottom_left = *(cell + (height  - 1));
		if(bottom_left){neighbours++;}
	}
	if( i < width && j < height){
		bottom_right = *(cell + (height + 1));
		if(bottom_right){neighbours++;}
	}
	if(i > 0 && j < height){
		upper_right = *(cell - (height - 1));
		if(upper_right){neighbours++;}	
	}
	if(i > 0 && j > 0){
		upper_left = *(cell - (height + 1));
		if(upper_left){neighbours++;}
	}
	if(*cell){ 
		if( neighbours < 2 || neighbours > 3){
			(*newcell) = 0;
		}
		else{
			(*newcell) = 1;
		}
	}
	else{
		if(neighbours == 3){
			(*newcell) = 1;
		}
	}
}

void update_grid(char array[width][height]){
	char new_array[width][height];
	init_grid(new_array);
	for(unsigned int i = 0; i < width; i++){
		for(unsigned int j = 0; j < height; j++){
			check_neighbours(&array[i][j], &new_array[i][j], i, j);
		}
	}
	for(unsigned int i = 0; i < width; i++){
		for(unsigned int j = 0; j < height; j++){
			array[i][j] = new_array[i][j];
		}
	}
}
