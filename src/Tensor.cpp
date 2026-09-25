#include "pulse/Tensor.hpp"

#include <algorithm>
#include <random>
#include <stdexcept>

namespace pulse {

Tensor::Tensor() : rows_(0), cols_(0) {}

Tensor::Tensor(std::size_t rows, std::size_t cols)
    : rows_(rows), cols_(cols), data_(rows * cols, 0.0f) {}

Tensor::Tensor(std::size_t rows, std::size_t cols, float fillValue)
    : rows_(rows), cols_(cols), data_(rows * cols, fillValue) {}

std::size_t Tensor::rows() const {
    return rows_;
}

std::size_t Tensor::cols() const {
    return cols_;
}

float& Tensor::at(std::size_t row, std::size_t col) {
    return data_[row * cols_ + col];
}

float Tensor::at(std::size_t row, std::size_t col) const {
    return data_[row * cols_ + col];
}

Tensor Tensor::multiply(const Tensor& other) const {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Tensor::multiply dimension mismatch");
    }

    Tensor result(rows_, other.cols_);
    for (std::size_t r = 0; r < rows_; ++r) {
        for (std::size_t c = 0; c < other.cols_; ++c) {
            float sum = 0.0f;
            for (std::size_t k = 0; k < cols_; ++k) {
                sum += at(r, k) * other.at(k, c);
            }
            result.at(r, c) = sum;
        }
    }
    return result;
}

Tensor Tensor::add(const Tensor& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Tensor::add dimension mismatch");
    }

    Tensor result(rows_, cols_);
    for (std::size_t i = 0; i < data_.size(); ++i) {
        result.data_[i] = data_[i] + other.data_[i];
    }
    return result;
}

Tensor Tensor::subtract(const Tensor& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Tensor::subtract dimension mismatch");
    }

    Tensor result(rows_, cols_);
    for (std::size_t i = 0; i < data_.size(); ++i) {
        result.data_[i] = data_[i] - other.data_[i];
    }
    return result;
}

Tensor Tensor::hadamard(const Tensor& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Tensor::hadamard dimension mismatch");
    }

    Tensor result(rows_, cols_);
    for (std::size_t i = 0; i < data_.size(); ++i) {
        result.data_[i] = data_[i] * other.data_[i];
    }
    return result;
}

Tensor Tensor::transpose() const {
    Tensor result(cols_, rows_);
    for (std::size_t r = 0; r < rows_; ++r) {
        for (std::size_t c = 0; c < cols_; ++c) {
            result.at(c, r) = at(r, c);
        }
    }
    return result;
}

Tensor Tensor::scale(float factor) const {
    Tensor result(rows_, cols_);
    for (std::size_t i = 0; i < data_.size(); ++i) {
        result.data_[i] = data_[i] * factor;
    }
    return result;
}

Tensor Tensor::apply(const std::function<float(float)>& fn) const {
    Tensor result(rows_, cols_);
    for (std::size_t i = 0; i < data_.size(); ++i) {
        result.data_[i] = fn(data_[i]);
    }
    return result;
}

void Tensor::fillZero() {
    std::fill(data_.begin(), data_.end(), 0.0f);
}

void Tensor::fillRandom(float minValue, float maxValue) {
    static std::mt19937 generator(std::random_device{}());
    std::uniform_real_distribution<float> distribution(minValue, maxValue);
    for (auto& value : data_) {
        value = distribution(generator);
    }
}

std::vector<float>& Tensor::data() {
    return data_;
}

const std::vector<float>& Tensor::data() const {
    return data_;
}

}
