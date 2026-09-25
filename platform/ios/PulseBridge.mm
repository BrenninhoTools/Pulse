#import "PulseBridge.h"

#include <memory>
#include <vector>

#include "pulse/DenseLayer.hpp"
#include "pulse/Network.hpp"
#include "pulse/Trainer.hpp"

@implementation PulseBridge {
    std::unique_ptr<pulse::Network> _network;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        _network = std::make_unique<pulse::Network>();
        _network->addLayer(std::make_unique<pulse::DenseLayer>(2, 4, pulse::ActivationType::Tanh));
        _network->addLayer(std::make_unique<pulse::DenseLayer>(4, 1, pulse::ActivationType::Sigmoid));
    }
    return self;
}

- (float)trainXorWithEpochs:(NSInteger)epochs {
    const float samples[4][2] = {{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}};
    const float labels[4] = {0.0f, 1.0f, 1.0f, 0.0f};

    std::vector<pulse::Tensor> inputs;
    std::vector<pulse::Tensor> targets;
    for (int i = 0; i < 4; ++i) {
        pulse::Tensor input(1, 2);
        input.at(0, 0) = samples[i][0];
        input.at(0, 1) = samples[i][1];
        inputs.push_back(input);

        pulse::Tensor target(1, 1);
        target.at(0, 0) = labels[i];
        targets.push_back(target);
    }

    pulse::Trainer trainer(*_network, 0.5f);
    return trainer.fit(inputs, targets, static_cast<std::size_t>(epochs));
}

- (NSArray<NSNumber *> *)predictWithInput:(NSArray<NSNumber *> *)input {
    pulse::Tensor tensorInput(1, static_cast<std::size_t>(input.count));
    for (NSUInteger i = 0; i < input.count; ++i) {
        tensorInput.at(0, static_cast<std::size_t>(i)) = input[i].floatValue;
    }

    pulse::Tensor output = _network->predict(tensorInput);

    NSMutableArray<NSNumber *> *result = [NSMutableArray arrayWithCapacity:output.cols()];
    for (std::size_t i = 0; i < output.cols(); ++i) {
        [result addObject:@(output.at(0, i))];
    }
    return result;
}

@end
