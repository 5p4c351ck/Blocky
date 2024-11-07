#include "Tensor.hpp"

void Tensor::clear(){
    dataCurrent.clear();
}

void Tensor::swap(){
	std::swap(dataCurrent, dataNext);
}

size_t Tensor::size() const{
    dataCurrent.size();
}

size_t Tensor::dimensionNumber() const{
    return dimensions.size();
}


CellState Tensor::cell(const std::vector<size_t>& indices) const{
    return dataCurrent[computeIndex(indices)];
}

void Tensor::cell(const std::vector<size_t>& indices, CellState state){
    dataCurrent[computeIndex(indices)] = state;
}

void Tensor::initializeStrides() {
            strides.resize(dimensions.size());
            size_t stride = 1;
            for (size_t i = dimensions.size(); i-- > 0;) {
                strides[i] = stride;
                stride *= dimensions[i];
            }
        }

size_t Tensor::computeIndex(const std::vector<size_t>& indices) const {
    if (indices.size() != dimensions.size()) {
        return -1;
    }
    size_t flat_index = 0;
    for (size_t i = 0; i < indices.size(); ++i) {
        if (indices[i] >= dimensions[i]) {
            return -1;
        }
        flat_index += indices[i] * strides[i];
    }
    return flat_index;
}