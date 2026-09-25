#pragma once

#include <cstddef>
#include <vector>

#include "pulse/Network.hpp"
#include "pulse/Tensor.hpp"

namespace pulse {

class Trainer {
public:
    Trainer(Network& network, float learningRate);

    float fit(const std::vector<Tensor>& inputs, const std::vector<Tensor>& targets, std::size_t epochs);

private:
    Network& network_;
    float learningRate_;
};

}
