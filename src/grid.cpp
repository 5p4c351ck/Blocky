#include "grid.hpp"



void Grid::swapGrid(){
	std::swap(current_depth, next_depth);
}

void Grid1d::clearGrid(){
    tensor.clear();
}

void Grid1d::pseudorandomPopulateGrid(){
    int lower_bound = 1;
    int upper_bound = 100;
    for(unsigned int i = 0; i < tensor_width; i++){
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distr(lower_bound, upper_bound);
		    int random_number = distr(gen) % 2;
			tensor[i][current_depth] = static_cast<CellState>(random_number);
	}
	return;
}

std::vector<CellState> Grid1d::getNeighbours (unsigned int width, unsigned int height) const{
		std::vector<CellState> neighbours;
		if(width > 0 && width < tensor.size()){
			neighbours.push_back(tensor[width - 1][current_depth]);
		}
		if(width < tensor.size()){
			neighbours.push_back(tensor[width][current_depth]);
		}
		if(width < tensor.size() - 1){
			neighbours.push_back(tensor[width + 1][current_depth]);
		}
		return neighbours;
}



void Grid2d::clearGrid(){
    tensor.clear();
}

void Grid2d::pseudorandomPopulateGrid(){
    int lower_bound = 1;
    int upper_bound = 100;
    for(unsigned int i = 0; i < tensor_width; i++){
		for(unsigned int j = 0; i < tensor_height; i++){
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distr(lower_bound, upper_bound);
		    int random_number = distr(gen) % 2;
			tensor[i][j][current_depth] = static_cast<CellState>(random_number);
		}
	}
	return;
}

std::vector<CellState> Grid2d::getNeighbours(unsigned int width, unsigned int height) const{
	std::vector<CellState> neighbours;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) continue;
			int nx = width + i;
			int ny = height + j;
			if (nx >= 0 && nx < tensor.size() && ny >= 0 && ny < tensor.size()) {
				neighbours.push_back(tensor[nx][ny][current_depth]);
			}
		}
	}
	return neighbours;
}


