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

unsigned int CellularAutomata::alive(){return gridInstance.alive();}
unsigned int CellularAutomata::dead(){return gridInstance.dead();}
unsigned int CellularAutomata::cellsAll(){return gridInstance.cellsAll();}


