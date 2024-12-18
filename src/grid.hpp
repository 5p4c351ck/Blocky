#ifndef GRID_HPP
#define GRID_HPP

#include<vector>
#include<chrono>
#include<random>

#include "Tensor.hpp"

enum class CellState {DEAD, ALIVE};


struct CellStatus{
        unsigned int cellNum;
        unsigned int aliveCount;
        unsigned int deadCount;
};

class Grid {
    public:
        Grid(std::vector<size_t> dims) : tensor(dims) {
            	cellStatus.cellNum = tensor.size();
        }
        ~Grid() = default;
        /* API */
        void clearGrid();
        void pseudorandomPopulateGrid();
        void updateGrid(unsigned int ruleNumber);
        const Tensor& getTensor() const;
        const CellStatus& getCellStatus() const;
    private:
        std::vector<CellState> getNeighborhood (size_t width, size_t height, size_t depth) const;
        CellState applyRule(unsigned int ruleNumber, const std::vector<CellState>& neighborhood);
        void setDeadCellCount(unsigned int aliveCells);
        Tensor tensor;
        CellStatus cellStatus;
        unsigned int randomSeed;
};
#endif


  



