#ifndef TENSOR_HPP
#define TENSOR_HPP

#include <vector>
#include <cstddef>
#include <initializer_list>

enum class CellState;

class Tensor{
    public:
        Tensor(std::initializer_list<size_t> dims) : dimensions(dims) {
        size_t capacity = 1;
        for (size_t dim : dimensions) {
            capacity *= dim;
        }
        dataCurrent.resize(capacity);
        dataNext.resize(capacity);
        initializeStrides();
    }
        void clear();
        void swap();
        size_t size() const;
        size_t dimensionNumber() const;
        CellState cell(size_t width, size_t height, size_t depth) const;
        void cell(size_t width, size_t height, size_t depths, CellState state);
    private:
        std::vector<size_t> dimensions;
        std::vector<size_t> strides;
        std::vector<CellState> dataCurrent;
        std::vector<CellState> dataNext;
        void initializeStrides();
        size_t computeIndex(std::vector<size_t>& indices) const;
};
#endif