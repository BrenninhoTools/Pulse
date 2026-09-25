#include "pulse/Network.hpp"

namespace pulse {

void Network::addLayer(std::unique_ptr<Layer> layer) {
    layers_.push_back(std::move(layer));
}

Tensor Network::predict(const Tensor& input) {
    Tensor current = input;
    for (auto& layer : layers_) {
        current = layer->forward(current);
    }
    return current;
}

float Network::trainStep(const Tensor& input, const Tensor& target, float learningRate) {
    Tensor output = predict(input);

    Tensor error(output.rows(), output.cols());
    float loss = 0.0f;
    std::size_t elementCount = output.data().size();
    for (std::size_t i = 0; i < elementCount; ++i) {
        float diff = output.data()[i] - target.data()[i];
        error.data()[i] = 2.0f * diff / static_cast<float>(elementCount);
        loss += diff * diff;
    }
    loss /= static_cast<float>(elementCount);

    Tensor gradient = error;
    for (auto it = layers_.rbegin(); it != layers_.rend(); ++it) {
        gradient = (*it)->backward(gradient, learningRate);
    }

    return loss;
}

}
