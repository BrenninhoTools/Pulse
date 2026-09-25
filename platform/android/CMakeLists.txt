cmake_minimum_required(VERSION 3.16)
project(PulseAndroid LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PULSE_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../..)

add_library(pulse_android SHARED
    ${PULSE_ROOT}/src/Tensor.cpp
    ${PULSE_ROOT}/src/Activation.cpp
    ${PULSE_ROOT}/src/DenseLayer.cpp
    ${PULSE_ROOT}/src/Network.cpp
    ${PULSE_ROOT}/src/Trainer.cpp
    jni/PulseBridge.cpp
)

target_include_directories(pulse_android PRIVATE
    ${PULSE_ROOT}/include
    jni
)
