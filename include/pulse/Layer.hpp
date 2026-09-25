#pragma once

#include "pulse/Tensor.hpp"

namespace pulse {

class Layer {
public:
    virtual ~Layer() = default;
    virtual Tensor forward(const Tensor& input) = 0;
    virtual Tensor backward(const Tensor& outputGradient, float learningRate) = 0;
};

}
