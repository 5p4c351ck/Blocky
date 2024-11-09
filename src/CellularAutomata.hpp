#ifndef CELLULARAUTOMATA_HPP
#define CELLULARAUTOMATA_HPP



#include<functional>
#include<algorithm>
#include<memory>

#include "grid.hpp"
#include "caProperties.hpp"



class CellularAutomata  {
    public:
        CellularAutomata (const caProperties& prop) 
        : caproperties(prop), gridInstance(prop.dims)
        {   
            caproperties.ss = StateSpace::BINARY;
            caproperties.currentIteration = 0;
        }
        /* API */
        int step();
        void pseudorandomPattern();
        void properties(caProperties prop);
        caProperties properties() const;
    private:
        caProperties caproperties;
        Grid gridInstance;
};
#endif