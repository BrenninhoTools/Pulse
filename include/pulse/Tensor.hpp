#pragma once

#include <cstddef>
#include <functional>
#include <vector>

namespace pulse {

class Tensor {
public:
    Tensor();
    Tensor(std::size_t rows, std::size_t cols);
    Tensor(std::size_t rows, std::size_t cols, float fillValue);

    std::size_t rows() const;
    std::size_t cols() const;

    float& at(std::size_t row, std::size_t col);
    float at(std::size_t row, std::size_t col) const;

    Tensor multiply(const Tensor& other) const;
    Tensor add(const Tensor& other) const;
    Tensor subtract(const Tensor& other) const;
    Tensor hadamard(const Tensor& other) const;
    Tensor transpose() const;
    Tensor scale(float factor) const;
    Tensor apply(const std::function<float(float)>& fn) const;

    void fillZero();
    void fillRandom(float minValue, float maxValue);

    std::vector<float>& data();
    const std::vector<float>& data() const;

private:
    std::size_t rows_;
    std::size_t cols_;
    std::vector<float> data_;
};

}
