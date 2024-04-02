#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define width  80 	
#define height 30	

char dead[] = "\033[30m\xE2\x96\x88\033[0m";
char alive[] = "\xE2\x96\x88";

char grid[height][width]; 
			   
void populate_grid(char array[height][width]){
	for(unsigned int i = 0; i < height; i++){
		for(unsigned int j = 0; j < width; j++){
			usleep(10);	
			int random_number = rand() % 2;
			array[i][j] = random_number;
			}
		}
}

void print_grid(void){
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
		printf("\033[%d;%dH", 1, 1);
	return;
}


int main(void){

	srand(clock());

	while(1){	
	usleep(100000);
	populate_grid(grid);
	print_grid();
	}
	return 0;
}
