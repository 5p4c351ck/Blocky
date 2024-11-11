#include "CellularAutomata.hpp"

int CellularAutomata::step(){
    gridInstance.updateGrid(caproperties.ruleNumber);
    return caproperties.currentIteration += 1;
}


void CellularAutomata::grid(std::vector<std::vector<CellState>>& vec) const{
    std::vector<CellState> v;
    Tensor tensor = gridInstance.getTensor();
    if(caproperties.dm == Dimensionality::ONE_D){
        for(size_t i = 0; i < caproperties.gridWidth; i++){
            v.push_back(tensor.cell(i,0,0));
        }
        vec.push_back(v);
    }
}

void CellularAutomata::clearGrid(){
    gridInstance.clearGrid();
}

void CellularAutomata::pseudorandomPattern(){
    gridInstance.pseudorandomPopulateGrid();
}

void CellularAutomata::properties(caProperties prop){
    caproperties = prop;
}

const caProperties& CellularAutomata::properties() const{
    return caproperties;
}

const Tensor& CellularAutomata::gridTensor() const{
    return gridInstance.getTensor();
}

const CellStatus& CellularAutomata::getCellStatus() const {
    return gridInstance.getCellStatus();
}



