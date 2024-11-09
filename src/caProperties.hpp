#ifndef CAOPROPERTIES_HPP
#define CAOPROPERTIES_HPP


enum class Dimensionality       {ONE_D = 1, TWO_D, THREE_D};
enum class StateSpace           {BINARY, MULTI};
enum class NeighborhoodType     {VON_NEUMANN, MOORE};
enum class BoundaryCondition    {WRAP_AROUND, FIXED, REFLECTIVE};

struct caProperties{

    caProperties(std::vector<size_t> v) : dims(v) {
    }

    Dimensionality      dm;
    StateSpace          ss;
    NeighborhoodType    nt;
    BoundaryCondition   bc;
    unsigned int        ruleNumber;
    size_t              gridWidth;
    size_t              gridHeight;
    size_t              gridDepth;
    std::vector<size_t> dims;
    unsigned int        currentIteration;
    unsigned long long  maxSteps;
};
#endif