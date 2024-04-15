#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define width  50	
#define height 50
			  
extern char grid[height][width];

/* API */
void init_grid(char array[height][width]);
void populate_grid(char array[height][width]);
void print_grid(char array[height][width], SDL_Renderer* renderer, SDL_Rect* rect, SDL_Surface* surface);
void check_neighbours(char *cell, char *newcell, int i, int j);
void update_grid(char array[height][width]);

#endif