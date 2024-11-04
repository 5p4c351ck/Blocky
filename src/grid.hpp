#ifndef GRID_HPP
#define GRID_HPP

#include <chrono>
#include <vector>
#include <algorithm>
#include <random>



class Grid {
    public:

    Grid(int width,int height) : grid_width(width), grid_height(height) {
        grid.resize(grid_width, std::vector<std::vector<char>>(grid_height, std::vector<char>(grid_depth, ' ')));
        }
    Grid(const Grid& other) : grid_width(other.grid_width), grid_height(other.grid_height) {
        grid.resize(grid_width, std::vector<std::vector<char>>(grid_height, std::vector<char>(grid_depth, ' ')));
        }

    /* API */
    void clear_grid();
    void pseudorandom_populate_grid();
    int check_neighbours (int x, int y) const;
    void update_grid();

    private:
    int grid_width;
    int grid_height;
    int grid_depth = 2;
    int cell_num = grid_width * grid_height; 
    int current_depth = 0;
    int next_depth = 1;
    /* A tensor to double buffer */
    std::vector<std::vector<std::vector<char>>> grid;

    unsigned long long iterations = 0;
    /* microseconds */
    unsigned long delay;
    time_t time_of_snapshot;
};
#endif