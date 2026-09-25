#pragma once

#include <memory>
#include <vector>

#include "pulse/Layer.hpp"
#include "pulse/Tensor.hpp"

namespace pulse {

class Network {
public:
    void addLayer(std::unique_ptr<Layer> layer);
    Tensor predict(const Tensor& input);
    float trainStep(const Tensor& input, const Tensor& target, float learningRate);

private:
    std::vector<std::unique_ptr<Layer>> layers_;
};

}
