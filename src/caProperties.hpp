#ifndef CAOPROPERTIES_HPP
#define CAOPROPERTIES_HPP


enum class Dimensionality       {ONE_D = 1, TWO_D, THREE_D};
enum class StateSpace           {BINARY, MULTI};
enum class NeighborhoodType     {VON_NEUMANN, MOORE};
enum class BoundaryCondition    {WRAP_AROUND, FIXED, REFLECTIVE};

struct caProperties{ 

    caProperties(size_t width) : il({width}) {
        dm = Dimensionality::ONE_D;
    };
    caProperties(size_t width, size_t height) : il({width, height}) {
        dm = Dimensionality::TWO_D;
    };
    caProperties(size_t width, size_t height, size_t depth) : il({width, height, depth}) {
        dm = Dimensionality::THREE_D;
    };

    Dimensionality      dm;
    StateSpace          ss;
    NeighborhoodType    nt;
    BoundaryCondition   bc;
    unsigned int        ruleNumber;
    size_t              gridWidth;
    size_t              gridHeight;
    size_t              gridDepth;
    std::initializer_list<size_t> il;
    unsigned int        currentIteration;
    unsigned long long  maxSteps;
};
#endif