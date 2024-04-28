#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/* 16:9 aspect ratio */
#define GRID_NUM 2
#define WIDTH  80	
#define HEIGHT 45
#define CELL_NUM WIDTH * HEIGHT

#define SQUARE_WIDTH 10
#define SQUARE_HEIGHT 10

/* microseconds */
extern unsigned long delay;

/* A tensor to double buffer */
extern char grid[GRID_NUM][WIDTH][HEIGHT];

struct snapshot {
	/* To be added
	 * Time of snapshot
	 * Starting pattern
	 */
	unsigned long long iterations;
	unsigned long delay;
	char grid[GRID_NUM][WIDTH][HEIGHT];
};

/* API */
void clear_grid(char array[GRID_NUM][WIDTH][HEIGHT]);
void populate_grid(char array[GRID_NUM][WIDTH][HEIGHT], int current_grid);
int print_grid(char array[GRID_NUM][WIDTH][HEIGHT], SDL_Renderer* renderer, SDL_Rect* rect, SDL_Surface* surface, int xOffset, int yOffset, int current_grid);
int check_neighbours(char array[GRID_NUM][WIDTH][HEIGHT], int x, int y, int current_grid);
void update_grid(char array[GRID_NUM][WIDTH][HEIGHT], int* current_grid, int* next_grid);

#endif
