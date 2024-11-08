#ifndef GRID_HPP
#define GRID_HPP

#include<vector>
#include<chrono>
#include<random>

#include "Tensor.hpp"

enum class CellState {DEAD, ALIVE};

class Grid {
    public:
        Grid(std::initializer_list<size_t> dims) : tensor(dims) {}
        ~Grid() = default;
        /* API */
        void clearGrid();
        void pseudorandomPopulateGrid();
        void updateGrid(unsigned int ruleNumber);
    private:
        std::vector<CellState> getNeighborhood (size_t width, size_t height, size_t depth) const;
        CellState applyRule(unsigned int ruleNumber, const std::vector<CellState>& neighborhood);
        Tensor tensor;
        unsigned int cellNum;
        int aliveCount;
        int deadCount;
        unsigned int randomSeed;
};
#endif


  



