#include "Tensor.hpp"

void Tensor::clear(){
    dataCurrent.clear();
}

void Tensor::swap(){
	std::swap(dataCurrent, dataNext);
}

size_t Tensor::size() const{
    return dataCurrent.size();
}

size_t Tensor::dimensionNumber() const{
    return dimensions.size();
}


CellState Tensor::cell(size_t width, size_t height, size_t depth) const{
    std::vector<size_t> indices{width,height,depth};
    indices.resize(dimensionNumber());
    return dataCurrent[computeIndex(indices)];
}

void Tensor::cell(size_t width, size_t height, size_t depth, CellState state){
    std::vector<size_t> indices{width,height,depth};
    indices.resize(dimensionNumber());
    dataNext[computeIndex(indices)] = state;
}

void Tensor::initializeStrides() {
            strides.resize(dimensions.size());
            size_t stride = 1;
            for (size_t i = dimensions.size(); i-- > 0;) {
                strides[i] = stride;
                stride *= dimensions[i];
            }
        }

size_t Tensor::computeIndex(std::vector<size_t>& indices) const {
    size_t flat_index = 0;
    for (size_t i = 0; i < indices.size(); ++i) {
        if (indices[i] >= dimensions[i]) {
            indices[i] = (dimensions[i] - 1);
        }
        flat_index += indices[i] * strides[i];
    }
    return flat_index;
}