#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define width  80 	
#define height 30	

char dead[] = "\033[30m\xE2\x96\x88\033[0m";
char alive[] = "\xE2\x96\x88";

char grid[height][width]; 
			   
static char under;		
static char above; 
static char right;
static char left;
static char bottom_left;
static char bottom_right; 
static char upper_right;	
static char upper_left;	 

void init_grid(char array[height][width]){
	for(unsigned int i = 0; i < height; i++){
		for(unsigned int j = 0; j < width; j++){
			array[i][j] = 0;
		}
	}	
}

void populate_grid(char array[height][width]){
	for(unsigned int i = 0; i < height; i++){
		for(unsigned int j = 0; j < width; j++){
			usleep(10);	
			int random_number = rand() % 2;
			array[i][j] = random_number;
			}
		}
	return;
}

void print_grid(void){
	printf("\033[%d;%dH", 1, 1);
	for(unsigned int i = 0; i < height; i++){
		for(unsigned int j = 0; j < width; j++){
			if(grid[i][j] == 1){
				printf("%s",alive);	
			}
			else{
				printf("%s", dead);
			}
		}
		printf("\n");
	}
		printf("\033[2J");
	return;
}

void check_neighbours(char *cell, char *newcell, int i, int j){
	
	unsigned int neighbours = 0;

	if(i < height){
		under = *(cell + width);
		if(under){neighbours++;}
	}
	if(i > 0){
		above = *(cell - width);
		if(above){neighbours++;}
	}
	if(j < width){
		right = *(cell + 1);
		if(right){neighbours++;}
	}
	if(j > 0){
		left = *(cell - 1);
		if(left){neighbours++;}
	}
	if(i < height && j > 0){
		bottom_left = *(cell + (width  - 1));
		if(bottom_left){neighbours++;}
	}
	if( i < height && j < width){
		bottom_right = *(cell + (width + 1));
		if(bottom_right){neighbours++;}
	}
	if(i > 0 && j < width){
		upper_right = *(cell - (width - 1));
		if(upper_right){neighbours++;}	
	}
	if(i > 0 && j > 0){
		upper_left = *(cell - (width + 1));
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

void update_grid(char array[height][width]){
	char new_array[height][width];
	init_grid(new_array);
	for(unsigned int i = 0; i < height; i++){
		for(unsigned int j = 0; j < width; j++){
			check_neighbours(&array[i][j], &new_array[i][j], i, j);
		}
	}
	for(unsigned int i = 0; i < height; i++){
		for(unsigned int j = 0; j < width; j++){
			array[i][j] = new_array[i][j];
		}
	}
}

int main(void){

	srand(clock());
	init_grid(grid);
	populate_grid(grid);	
	
	/*
	 * GLIDER
	grid[8][11] = 1;
	grid[9][12] = 1;
	grid[10][10] = 1;
	grid[10][11] = 1;
	grid[10][12] = 1;
	*/

	long int x = 0;
	long int y = 1;

	while(1){

	usleep(100000);

	if(y > x && x <= 300){
			
		grid[1][10] = 1;
		grid[2][11] = 1;
		grid[3][9] = 1;
		grid[3][10] = 1;
		grid[3][11] = 1;
		
		grid[1][60] = 1;
		grid[2][59] = 1;
		grid[3][59] = 1;
		grid[3][60] = 1;
		grid[3][61] = 1;
		
		x += 20;
	}

	print_grid();
	update_grid(grid);
	y++;
	}
	return 0;
}
