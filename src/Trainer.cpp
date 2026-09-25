#include "pulse/Trainer.hpp"

#include <stdexcept>

namespace pulse {

Trainer::Trainer(Network& network, float learningRate)
    : network_(network), learningRate_(learningRate) {}

float Trainer::fit(const std::vector<Tensor>& inputs, const std::vector<Tensor>& targets, std::size_t epochs) {
    if (inputs.size() != targets.size()) {
        throw std::invalid_argument("inputs and targets must have the same size");
    }

    float lastLoss = 0.0f;
    for (std::size_t epoch = 0; epoch < epochs; ++epoch) {
        float epochLoss = 0.0f;
        for (std::size_t i = 0; i < inputs.size(); ++i) {
            epochLoss += network_.trainStep(inputs[i], targets[i], learningRate_);
        }
        lastLoss = epochLoss / static_cast<float>(inputs.size());
    }
    return lastLoss;
}

}
