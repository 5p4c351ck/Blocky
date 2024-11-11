#include "grid.hpp"

void Grid::clearGrid(){
    tensor.clear();
}

void Grid::pseudorandomPopulateGrid(){
    int lower_bound = 1;
    int upper_bound = 100;
	std::random_device rd;
	randomSeed = rd();
	std::mt19937 gen(randomSeed);
	std::uniform_int_distribution<> distr(lower_bound, upper_bound);
	int aliveCells = 0;
    for(size_t i = 0; i < tensor.size(); i++){
		int random_number = distr(gen) % 2;
		if(random_number){aliveCells += 1;}
		tensor.cell(i, 0, 0, static_cast<CellState>(random_number));
	}
	cellStatus.aliveCount = aliveCells;
	setDeadCellCount(cellStatus.aliveCount);
	return;
}

void Grid::updateGrid(unsigned int ruleNumber){
	std::vector<CellState> neighborhood;
	CellState state;
	int aliveCells = 0;
	if(tensor.dimensionNumber() == 1){
		for(size_t i = 0; i < tensor.size(); i++){
			neighborhood = getNeighborhood(i,0,0);
			state = applyRule(ruleNumber, neighborhood);
			tensor.cell(i, 0, 0, state);
			if(static_cast<int>(state)){
				aliveCells += 1;
			}
		}
	}
	cellStatus.aliveCount = aliveCells;
	setDeadCellCount(cellStatus.aliveCount);
	tensor.swap();
}

const Tensor& Grid::getTensor() const {
	return tensor;
}


const CellStatus& Grid::getCellStatus() const {
	return cellStatus;
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
    int neighbors = ( (static_cast<int>(neighborhood[0])) << 2) | ((static_cast<int>(neighborhood[1])) << 1) | (static_cast<int>(neighborhood[2]));
    return static_cast<CellState>(((ruleNumber >> neighbors) & 1));
}

void Grid::setDeadCellCount(unsigned int aliveCells){
	cellStatus.deadCount = cellStatus.cellNum - aliveCells;
}
