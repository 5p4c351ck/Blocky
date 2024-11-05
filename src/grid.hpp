#ifndef GRID_HPP
#define GRID_HPP

#include<vector>
#include <chrono>
#include <random>



enum class CellState {DEAD, ALIVE};

class Grid {
    public:
        virtual ~Grid(){}
        /* API */
        virtual void clearGrid() = 0;
        virtual void pseudorandomPopulateGrid() = 0;
        //virtual void updateGrid()= 0;
        void swapGrid();
    protected:
        virtual std::vector<CellState> getNeighbours (unsigned int width, unsigned int height) const = 0;
        int tensor_width;
        int tensor_height;
        int tensor_depth = 2;
        int current_depth = 0;
        int next_depth = 1;
};

class Grid1d: public Grid {
    public:
        Grid1d(int width, int height){
            tensor_width = width;
            tensor_height = height;
            tensor.resize(tensor_width, std::vector<CellState>(tensor_depth, CellState::DEAD));
            }
        Grid1d(const Grid1d& other){
            tensor_width = other.tensor_width;
            tensor_height = other.tensor_height;
            tensor.resize(tensor_width, std::vector<CellState>(tensor_depth, CellState::DEAD));
            }
        /* API */
        void clearGrid() override;
        void pseudorandomPopulateGrid() override;
        //void updateGrid() override;
    private:
        std::vector<CellState> getNeighbours (unsigned int width, unsigned int height) const override;
        int cell_num = tensor_width; 
        unsigned int randomSeed;
        unsigned int currentIteration;
        int aliveCount;
        int deadCount;
        std::vector<std::vector<CellState>> tensor;
};

class Grid2d: public Grid {
    public:
        Grid2d(int width,int height){
            tensor_width = width;
            tensor_height = height;
            tensor.resize(tensor_width, std::vector<std::vector<CellState>>(tensor_height, std::vector<CellState>(tensor_depth, CellState::DEAD)));
            }
        Grid2d(const Grid2d& other){
            tensor_width = other.tensor_width;
            tensor_height = other.tensor_height;
            tensor.resize(tensor_width, std::vector<std::vector<CellState>>(tensor_height, std::vector<CellState>(tensor_depth, CellState::DEAD)));
            }
        /* API */
        void clearGrid() override;
        void pseudorandomPopulateGrid() override;
        //void updateGrid() override;
    private:
        std::vector<CellState> getNeighbours (unsigned int width, unsigned int height) const override;
        int cell_num = tensor_width * tensor_height;
        unsigned int randomSeed;
        unsigned int currentIteration;
        int aliveCount;
        int deadCount;
        std::vector<std::vector<std::vector<CellState>>> tensor;
};
#endif