#include "CellularAutomata.hpp"

int CellularAutomata::step(){
    gridInstance.updateGrid(caproperties.ruleNumber);
    return caproperties.currentIteration += 1;
}

void CellularAutomata::pseudorandomPattern(){
    gridInstance.pseudorandomPopulateGrid();
}

void CellularAutomata::properties(caProperties prop){
    return;
}

caProperties CellularAutomata::properties() const{
    return caproperties;
}


