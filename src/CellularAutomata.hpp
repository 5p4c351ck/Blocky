#ifndef CELLULARAUTOMATA_HPP
#define CELLULARAUTOMATA_HPP



#include<functional>
#include<algorithm>
#include<memory>



#include "grid.hpp"
#include "caProperties.hpp"



class CellularAutomata  {
    public:
        CellularAutomata (const caProperties& prop) : caproperties(prop) {
            if(caproperties.dm == Dimensionality::ONE_D){
                gridInstance = std::make_unique<Grid1d>(prop.gridWidth, 0);
            }
            else if(caproperties.dm == Dimensionality::TWO_D){
                gridInstance = std::make_unique<Grid2d>(prop.gridWidth, prop.gridHeight);
            }
            else if(caproperties.dm == Dimensionality::THREE_D){
                gridInstance = nullptr;
            }
            caproperties.currentIteration = 0;
        }
        /* API */
        int step();
        void properties(caProperties prop);
        caProperties properties() const;
    private:
        caProperties caproperties;
        std::unique_ptr<Grid> gridInstance;
};
#endif