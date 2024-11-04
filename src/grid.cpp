#include "grid.hpp"



void Grid::swap_grid(){
	std::swap(current_depth, next_depth);
}

void Grid1d::clearGrid(){
    tensor.clear();
}

void Grid1d::pseudorandomPopulate_grid(){
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

std::vector<CellState> Grid1d::getNeighbours(unsigned int x) const{
		std::vector<CellState> neighbours;
		if(x > 0 && x < tensor.size()){
			neighbours.push_back(tensor[x - 1][current_depth]);
		}
		if(x < tensor.size()){
			neighbours.push_back(tensor[x][current_depth]);
		}
		if(x < tensor.size() - 1){
			neighbours.push_back(tensor[x + 1][current_depth]);
		}
		return neighbours;
}


