#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

/* Maintain the 16:9 aspect ratio */
#define grid_num 2
#define width  80	
#define height 45

#define square_width 10
#define square_height 10

extern char grid[grid_num][width][height];

/* API */
void init_grid(char array[grid_num][width][height], int current_grid);
void populate_grid(char array[grid_num][width][height], int current_grid);
void print_grid(char array[grid_num][width][height], SDL_Renderer* renderer, SDL_Rect* rect, SDL_Surface* surface, int xOffset, int yOffset, int current_grid);
int check_neighbours(char array[grid_num][width][height], int x, int y, int current_grid);
void update_grid(char array[grid_num][width][height], int* current_grid, int* next_grid);

#endif
