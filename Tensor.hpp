#include <iostream>
#include <vector>
#include <numeric>
#include <cstdlib> 

class Tensor {
public:
    std::vector<int64_t> shape; // shape of tensor
    std::vector<int64_t> strides; // stride is the number of elements to skip to get to the next element in that dimension
    float* data = nullptr; // points to memeory big enaough to hold the size of the tensor as a vlaue e.g 6
    size_t size = 0; // start with 0

    Tensor(std::vector<int64_t> dims) : shape(dims) {
        // 1. Calculate total number of elements
        size = std::accumulate(dims.begin(), dims.end(), 1, std::multiplies<int64_t>());


        size_t bytes = size * sizeof(float);
        size_t aligned_size = ((bytes + 63) / 64) * 64; 
        
        data = (float*)std::aligned_alloc(64, aligned_size);

        if (!data) throw std::runtime_error("Failed to allocate aligned memory.");


        strides.resize(shape.size());
        int64_t current_stride = 1;
        for (int i = shape.size() - 1; i >= 0; --i) {
            strides[i] = current_stride;
            current_stride *= shape[i];
        }
    }

    ~Tensor() { std::free(data); }

    // Helper to check if memory is actually aligned
    bool is_aligned() const {
        return (reinterpret_cast<uintptr_t>(data) % 64 == 0);
    }

    float& operator[] (size_t index) {
        return data[index];
    }

    float& at(const std::vector<int64_t>& indices) {
        size_t index = 0;
        for (size_t i = 0; i < indices.size(); ++i) {
            index += indices[i] * strides[i];
        }
        return data[index]; 
}

    void reshape(const std::vector<int64_t>& new_shape) {
        size = std::accumulate(new_shape.begin(), new_shape.end(), 1, std::multiplies<int64_t>());
        shape = new_shape;
        strides.resize(shape.size());
        int64_t current_stride = 1;
        for (int i = shape.size() - 1; i >= 0; --i) {
            strides[i] = current_stride;
            current_stride *= shape[i];
        }   
        
    }

};