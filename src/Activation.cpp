#include "pulse/Activation.hpp"

#include <algorithm>
#include <cmath>

namespace pulse {

float activationForward(ActivationType type, float x) {
    switch (type) {
        case ActivationType::Sigmoid:
            return 1.0f / (1.0f + std::exp(-x));
        case ActivationType::Relu:
            return std::max(0.0f, x);
        case ActivationType::Tanh:
            return std::tanh(x);
        case ActivationType::Linear:
        default:
            return x;
    }
}

float activationDerivative(ActivationType type, float activatedValue) {
    switch (type) {
        case ActivationType::Sigmoid:
            return activatedValue * (1.0f - activatedValue);
        case ActivationType::Relu:
            return activatedValue > 0.0f ? 1.0f : 0.0f;
        case ActivationType::Tanh:
            return 1.0f - activatedValue * activatedValue;
        case ActivationType::Linear:
        default:
            return 1.0f;
    }
}

}
