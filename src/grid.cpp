#include "grid.hpp"

void Grid::clear_grid(){
    grid.clear();
}

void Grid::pseudorandom_populate_grid(){
    int lower_bound = 1;
    int upper_bound = 100;
    for(unsigned int i = 0; i < grid_width; i++){
		for(unsigned int j = 0; j < grid_height; j++){
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distr(lower_bound, upper_bound);
		    int random_number = distr(gen) % 2;
			grid[i][j][current_depth] = random_number;
			}
		}
	return;
}

int Grid::check_neighbours(int x, int y) const{
	int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < grid_width && ny >= 0 && ny < grid_height) {
                count += grid[nx][ny][current_depth];
            }
        }
    }
    return count;
}

void Grid::update_grid(){
	for (int i = 0; i < grid_width; i++) {
        	for (int j = 0; j < grid_height; j++) {
            		int neighbors = check_neighbours(i, j);
            		if (grid[i][j][next_depth] == 1) {
                		if (neighbors < 2 || neighbors > 3) {
                    			grid[i][j][next_depth] = 0; /*Cell dies due to underpopulation or overcrowding*/
                		}else {
                    			grid[i][j][next_depth] = 1; /*Cell survives*/
                		}
            		}else {
                		if (neighbors == 3) {
                    			grid[i][j][next_depth] = 1; /*Cell is born*/
                		} else {
                    			grid[i][j][next_depth] = 0; /*Cell remains dead*/
                		}
            		}
        	}
    }
    std::swap(current_depth, next_depth);
}