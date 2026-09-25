#include "PulseBridge.h"

#include <memory>
#include <vector>

#include "pulse/DenseLayer.hpp"
#include "pulse/Network.hpp"
#include "pulse/Trainer.hpp"

namespace {

pulse::Network* toNetwork(jlong handle) {
    return reinterpret_cast<pulse::Network*>(handle);
}

}

extern "C" {

JNIEXPORT jlong JNICALL Java_com_pulse_app_PulseBridge_nativeCreateNetwork(JNIEnv*, jobject) {
    auto* network = new pulse::Network();
    network->addLayer(std::make_unique<pulse::DenseLayer>(2, 4, pulse::ActivationType::Tanh));
    network->addLayer(std::make_unique<pulse::DenseLayer>(4, 1, pulse::ActivationType::Sigmoid));
    return reinterpret_cast<jlong>(network);
}

JNIEXPORT void JNICALL Java_com_pulse_app_PulseBridge_nativeDestroyNetwork(JNIEnv*, jobject, jlong handle) {
    delete toNetwork(handle);
}

JNIEXPORT jfloat JNICALL Java_com_pulse_app_PulseBridge_nativeTrainXor(JNIEnv*, jobject, jlong handle, jint epochs) {
    pulse::Network* network = toNetwork(handle);

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

    pulse::Trainer trainer(*network, 0.5f);
    float loss = trainer.fit(inputs, targets, static_cast<std::size_t>(epochs));
    return loss;
}

JNIEXPORT jfloatArray JNICALL Java_com_pulse_app_PulseBridge_nativePredict(JNIEnv* env, jobject, jlong handle, jfloatArray input) {
    pulse::Network* network = toNetwork(handle);

    jsize inputLength = env->GetArrayLength(input);
    std::vector<jfloat> inputBuffer(static_cast<std::size_t>(inputLength));
    env->GetFloatArrayRegion(input, 0, inputLength, inputBuffer.data());

    pulse::Tensor tensorInput(1, static_cast<std::size_t>(inputLength));
    for (jsize i = 0; i < inputLength; ++i) {
        tensorInput.at(0, static_cast<std::size_t>(i)) = inputBuffer[static_cast<std::size_t>(i)];
    }

    pulse::Tensor output = network->predict(tensorInput);

    jfloatArray result = env->NewFloatArray(static_cast<jsize>(output.cols()));
    std::vector<jfloat> outputBuffer(output.cols());
    for (std::size_t i = 0; i < output.cols(); ++i) {
        outputBuffer[i] = output.at(0, i);
    }
    env->SetFloatArrayRegion(result, 0, static_cast<jsize>(output.cols()), outputBuffer.data());

    return result;
}

}
