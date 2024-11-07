#include "grid.hpp"

void Grid::clearGrid(){
    tensor.clear();
}

void Grid::pseudorandomPopulateGrid(){
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

void Grid::updateGrid(unsigned int ruleNumber){
	std::vector<CellState> neighborhood;
	std::vector<size_t> ind(tensor.dimensionNumber());
	switch (tensor.dimensionNumber())
		{
		case 1:
			for(size_t i = 0; i < tensor.size(); i++){
				ind[0] = i;
				neighborhood = getNeighborhood(ind);
				tensor.cell(ind, applyRule(ruleNumber, neighborhood));
			}
			tensor.swap();
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}
}

std::vector<CellState> Grid::getNeighborhood (std::vector<size_t>& indices) const{
		indices.resize(tensor.dimensionNumber());
		std::vector<CellState> neighborhood;
		switch (tensor.dimensionNumber())
		{
		case 1:
			if(indices[0] > 0 && indices[0] < tensor.size()){
				indices[0]-=1;
				neighborhood.push_back(tensor.cell(indices));
			}
			else{
				neighborhood.push_back(CellState::DEAD);
			}
			if(indices[0] < tensor.size()){
				indices[0]+=1;
				neighborhood.push_back(tensor.cell(indices));
			}
			else{
				neighborhood.push_back(CellState::DEAD);
			}
			if(indices[0] < tensor.size() - 1){
				indices[0]+=1;
				neighborhood.push_back(tensor.cell(indices));
			}
			else{
				neighborhood.push_back(CellState::DEAD);
			}
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}
		return neighborhood;
}

CellState Grid1d::applyRule(unsigned int ruleNumber, const std::vector<CellState>& neighborhood) {
    int neighbors = (static_cast<int>(neighborhood[0]) << 2) |
				    (static_cast<int>(neighborhood[1]) << 1) | 
					(static_cast<int>(neighborhood[2]));
    return static_cast<CellState>(((ruleNumber >> neighbors) & 1));
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

