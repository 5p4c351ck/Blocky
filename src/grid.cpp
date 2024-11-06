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

void Grid1d::updateGrid(unsigned int ruleNumber){
	std::vector<CellState> neighborhood;
	for(unsigned int i = 0; i < tensor.size(); i++){
		neighborhood = getNeighborhood(i,0);
		tensor[i][next_depth] = applyRule(ruleNumber, neighborhood);
	}
	swapGrid();
}

std::vector<CellState> Grid1d::getNeighborhood (unsigned int cellWidth, unsigned int cellHeight) const{
		std::vector<CellState> neighborhood;
		if(cellWidth > 0 && cellWidth < tensor.size()){
			neighborhood.push_back(tensor[cellWidth - 1][current_depth]);
		}
		else{
			neighborhood.push_back(CellState::DEAD);
		}
		if(cellWidth < tensor.size()){
			neighborhood.push_back(tensor[cellWidth][current_depth]);
		}
		else{
			neighborhood.push_back(CellState::DEAD);
		}
		if(cellWidth < tensor.size() - 1){
			neighborhood.push_back(tensor[cellWidth + 1][current_depth]);
		}
		else{
			neighborhood.push_back(CellState::DEAD);
		}
		return neighborhood;
}

CellState Grid1d::applyRule(unsigned int ruleNumber, const std::vector<CellState>& neighborhood) {
    int neighbors = (static_cast<int>(neighborhood[0]) << 2) |
				    (static_cast<int>(neighborhood[1]) << 1) | 
					(static_cast<int>(neighborhood[2]));
    return static_cast<CellState>(((ruleNumber >> neighbors) & 1));
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

void Grid2d::updateGrid(unsigned int ruleNumber){
	return;
}

std::vector<CellState> Grid2d::getNeighborhood(unsigned int cellWidth, unsigned int cellHeight) const{
	std::vector<CellState> neighborhood;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) continue;
			int nx = cellWidth + i;
			int ny = cellHeight + j;
			if (nx >= 0 && nx < tensor.size() && ny >= 0 && ny < tensor.size()) {
				neighborhood.push_back(tensor[nx][ny][current_depth]);
			}
		}
	}
	return neighborhood;
}

CellState Grid2d::applyRule(unsigned int ruleNumber, const std::vector<CellState>& neighborhood){
	return CellState::DEAD;
}

