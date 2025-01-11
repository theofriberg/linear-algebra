cmake_minimum_required(VERSION 3.10)
project(NeuralNetwork)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

# Include the include directory for headers
include_directories(include)

# Collect all source files in the src directory
file(GLOB SOURCES "src/*.cpp")

# Define the library
add_library(neural_network_lib STATIC ${SOURCES})

# Specify include directories for the library
target_include_directories(neural_network_lib PUBLIC include)

# Define the main executable
add_executable(neural_network src/main.cpp)

# Link the library to the main executable
target_link_libraries(neural_network PRIVATE neural_network_lib)

# Add the tests subdirectory
add_subdirectory(tests)

# Enable testing
enable_testing()
