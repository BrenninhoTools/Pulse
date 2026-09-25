cmake_minimum_required(VERSION 3.16)
project(PulseIOS LANGUAGES CXX OBJCXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PULSE_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../..)

add_library(pulse_ios STATIC
    ${PULSE_ROOT}/src/Tensor.cpp
    ${PULSE_ROOT}/src/Activation.cpp
    ${PULSE_ROOT}/src/DenseLayer.cpp
    ${PULSE_ROOT}/src/Network.cpp
    ${PULSE_ROOT}/src/Trainer.cpp
    PulseBridge.mm
)

target_include_directories(pulse_ios PUBLIC
    ${PULSE_ROOT}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(pulse_ios PRIVATE $<$<COMPILE_LANGUAGE:OBJCXX>:-std=c++17>)

target_link_libraries(pulse_ios PUBLIC "-framework Foundation")
