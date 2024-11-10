#ifndef GRID_HPP
#define GRID_HPP

#include<vector>
#include<chrono>
#include<random>

#include "Tensor.hpp"

enum class CellState {DEAD, ALIVE};

class Grid {
    public:
        Grid(std::vector<size_t> dims) : tensor(dims) {
            	cellNum = tensor.size();
        }
        ~Grid() = default;
        /* API */
        void clearGrid();
        void pseudorandomPopulateGrid();
        void updateGrid(unsigned int ruleNumber);
        unsigned int alive();
        unsigned int dead();
        unsigned int cellsAll();     
    private:
        std::vector<CellState> getNeighborhood (size_t width, size_t height, size_t depth) const;
        CellState applyRule(unsigned int ruleNumber, const std::vector<CellState>& neighborhood);
        void setDeadCellCount(int aliveCells);
        Tensor tensor;
        unsigned int cellNum;
        unsigned int aliveCount;
        unsigned int deadCount;
        unsigned int randomSeed;
};
#endif


  



