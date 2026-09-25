#include "pulse/DenseLayer.hpp"

#include <cmath>

namespace pulse {

DenseLayer::DenseLayer(std::size_t inputSize, std::size_t outputSize, ActivationType activation)
    : weights_(inputSize, outputSize), bias_(1, outputSize), activation_(activation) {
    float limit = 1.0f / std::sqrt(static_cast<float>(inputSize));
    weights_.fillRandom(-limit, limit);
    bias_.fillZero();
}

Tensor DenseLayer::forward(const Tensor& input) {
    Tensor preActivation = input.multiply(weights_).add(bias_);
    Tensor output = preActivation.apply([this](float value) {
        return activationForward(activation_, value);
    });

    lastInput_ = input;
    lastOutput_ = output;
    return output;
}

Tensor DenseLayer::backward(const Tensor& outputGradient, float learningRate) {
    Tensor activationGradient = lastOutput_.apply([this](float value) {
        return activationDerivative(activation_, value);
    });
    Tensor deltaPre = outputGradient.hadamard(activationGradient);

    Tensor gradWeights = lastInput_.transpose().multiply(deltaPre);
    Tensor gradInput = deltaPre.multiply(weights_.transpose());

    weights_ = weights_.subtract(gradWeights.scale(learningRate));
    bias_ = bias_.subtract(deltaPre.scale(learningRate));

    return gradInput;
}

}
