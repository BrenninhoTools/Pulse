#include <iostream>
#include <memory>
#include <vector>

#include "pulse/DenseLayer.hpp"
#include "pulse/Network.hpp"
#include "pulse/Trainer.hpp"

int main() {
    pulse::Network network;
    network.addLayer(std::make_unique<pulse::DenseLayer>(2, 4, pulse::ActivationType::Tanh));
    network.addLayer(std::make_unique<pulse::DenseLayer>(4, 1, pulse::ActivationType::Sigmoid));

    std::vector<pulse::Tensor> inputs;
    std::vector<pulse::Tensor> targets;

    const float samples[4][2] = {{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}};
    const float labels[4] = {0.0f, 1.0f, 1.0f, 0.0f};

    for (int i = 0; i < 4; ++i) {
        pulse::Tensor input(1, 2);
        input.at(0, 0) = samples[i][0];
        input.at(0, 1) = samples[i][1];
        inputs.push_back(input);

        pulse::Tensor target(1, 1);
        target.at(0, 0) = labels[i];
        targets.push_back(target);
    }

    pulse::Trainer trainer(network, 0.5f);
    float finalLoss = trainer.fit(inputs, targets, 5000);

    std::cout << "Pulse core self-test\n";
    std::cout << "Final training loss: " << finalLoss << "\n";
    for (std::size_t i = 0; i < inputs.size(); ++i) {
        pulse::Tensor prediction = network.predict(inputs[i]);
        std::cout << samples[i][0] << " xor " << samples[i][1] << " = " << prediction.at(0, 0) << "\n";
    }

    return 0;
}
