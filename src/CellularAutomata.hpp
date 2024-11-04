#ifndef CELLULARAUTOMATA_HPP
#define CELLULARAUTOMATA_HPP


#include <chrono>
#include <vector>
#include <algorithm>
#include <random>

#include "grid.hpp"


enum class Dimensionality {ONE_D = 1, TWO_D, THREE_D};
enum class StateSpace {BINARY, MULTI};
enum class NeighborhoodType {VON_NEUMANN, MOORE};
enum class BoundaryCondition {WRAP_AROUND, FIXED, REFLECTIVE};
enum class CellState {DEAD, ALIVE};


class CellularAutomata  {
    public:
        CellularAutomata ();

        int step();
        void getSnapshot();
        Dimensionality dimensionality() const;
        void dimensionality(Dimensionality d);
        StateSpace getStateSpace();
        NeighborhoodType getNeighborhoodType();
        BoundaryCondition getBoundaryCondition();
        int getRule();
        unsigned long long getMaxSteps();
        void getGrid();

    private:
        Dimensionality dimensionality;
        StateSpace stateSpace;
        NeighborhoodType neighborhood;
        BoundaryCondition boundaryCondition;
        int rule;
        unsigned long long maxSteps;
        Grid* gridPointer;
}
#endif