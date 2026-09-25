#pragma once

namespace pulse {

enum class ActivationType {
    Linear,
    Sigmoid,
    Relu,
    Tanh
};

float activationForward(ActivationType type, float x);
float activationDerivative(ActivationType type, float activatedValue);

}
