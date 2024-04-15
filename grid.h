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
#define width  80	
#define height 45

#define square_width 10
#define square_height 10

extern char grid[width][height];

/* API */
void init_grid(char array[width][height]);
void populate_grid(char array[width][height]);
void print_grid(char array[width][height], SDL_Renderer* renderer, SDL_Rect* rect, SDL_Surface* surface, int windowWidth, int windowHeight);
void check_neighbours(char *cell, char *newcell, int i, int j);
void update_grid(char array[width][height]);

#endif
