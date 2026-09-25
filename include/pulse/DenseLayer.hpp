#pragma once

#include <cstddef>

#include "pulse/Activation.hpp"
#include "pulse/Layer.hpp"

namespace pulse {

class DenseLayer : public Layer {
public:
    DenseLayer(std::size_t inputSize, std::size_t outputSize, ActivationType activation);

    Tensor forward(const Tensor& input) override;
    Tensor backward(const Tensor& outputGradient, float learningRate) override;

private:
    Tensor weights_;
    Tensor bias_;
    Tensor lastInput_;
    Tensor lastOutput_;
    ActivationType activation_;
};

}
