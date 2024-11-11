#ifndef CELLULARAUTOMATA_HPP
#define CELLULARAUTOMATA_HPP



#include<functional>
#include<algorithm>
#include<memory>

#include "imgui.h"

#include "grid.hpp"
#include "caProperties.hpp"



class CellularAutomata  {
    public:
        CellularAutomata (const caProperties& prop) 
        : caproperties(prop), gridInstance(prop.dims)
        {   
            if(caproperties.dims.size() == 1){
                caproperties.dm = Dimensionality::ONE_D;
                caproperties.gridWidth = caproperties.dims[0];
            }
            else if(caproperties.dims.size() == 2){
                caproperties.dm = Dimensionality::TWO_D;
                caproperties.gridWidth = caproperties.dims[0];
                caproperties.gridHeight = caproperties.dims[1];
            }
            else if(caproperties.dims.size() == 3){
                caproperties.dm = Dimensionality::THREE_D;
                caproperties.gridWidth = caproperties.dims[0];
                caproperties.gridHeight = caproperties.dims[1];
                caproperties.gridDepth = caproperties.dims[2];
            }
            caproperties.ss = StateSpace::BINARY;
            caproperties.currentIteration = 0;
        }
        /* API */
        int step();
        void grid(std::vector<std::vector<CellState>>& vec) const;
        void pseudorandomPattern();
        void properties(caProperties prop);
        const caProperties& properties() const;
        const CellStatus& getCellStatus() const;
    private:
        const Tensor& gridTensor() const;
        caProperties caproperties;
        Grid gridInstance;
};
#endif