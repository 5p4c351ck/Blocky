#include "grid.hpp"

void Grid::clearGrid(){
    tensor.clear();
}

void Grid::pseudorandomPopulateGrid(){
    int lower_bound = 1;
    int upper_bound = 100;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(lower_bound, upper_bound);
    for(size_t i = 0; i < tensor.size(); i++){
		int random_number = distr(gen) % 2;
		tensor.cell(i, 0, 0, static_cast<CellState>(random_number));
	}
	return;
}

void Grid::updateGrid(unsigned int ruleNumber){
	std::vector<CellState> neighborhood;
	if(tensor.dimensionNumber() == 1){
		for(size_t i = 0; i < tensor.size(); i++){
			neighborhood = getNeighborhood(i,0,0);
			tensor.cell(i, 0, 0, applyRule(ruleNumber, neighborhood));
		}
	}
	tensor.swap();
}

std::vector<CellState> Grid::getNeighborhood (size_t width, size_t height, size_t depth)  const{
		std::vector<CellState> neighborhood;
		if(tensor.dimensionNumber() == 1){
			if(width > 0 && width < tensor.size()){
				neighborhood.push_back(tensor.cell(width - 1, 0, 0));
			}
			else{
				neighborhood.push_back(CellState::DEAD);
			}
			if(width < tensor.size()){
				neighborhood.push_back(tensor.cell(width, 0, 0));
			}
			else{
				neighborhood.push_back(CellState::DEAD);
			}
			if(width < tensor.size() - 1){
				neighborhood.push_back(tensor.cell(width + 1, 0, 0));
			}
			else{
				neighborhood.push_back(CellState::DEAD);
			}
		}
		return neighborhood;
}

CellState Grid::applyRule(unsigned int ruleNumber, const std::vector<CellState>& neighborhood) {
    int neighbors = (static_cast<int>(neighborhood[0]) << 2) |
				    (static_cast<int>(neighborhood[1]) << 1) | 
					(static_cast<int>(neighborhood[2]));
    return static_cast<CellState>(((ruleNumber >> neighbors) & 1));
}