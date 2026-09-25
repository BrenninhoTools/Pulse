cmake_minimum_required(VERSION 3.16)
project(Pulse LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(pulse_core STATIC
    src/Tensor.cpp
    src/Activation.cpp
    src/DenseLayer.cpp
    src/Network.cpp
    src/Trainer.cpp
)

target_include_directories(pulse_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(pulse_cli src/main.cpp)
target_link_libraries(pulse_cli PRIVATE pulse_core)
