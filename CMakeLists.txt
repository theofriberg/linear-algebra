cmake_minimum_required(VERSION 3.10)
project(LinearAlgebra)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

# Include the include directory for headers
include_directories(include)

# Collect all source files in the src directory
file(GLOB SOURCES "src/*.cpp")

# Define the library
add_library(linear_algebra_lib STATIC ${SOURCES})

# Specify include directories for the library
target_include_directories(linear_algebra_lib PUBLIC include)

# Define the main executable
add_executable(linear_algebra src/main.cpp)

# Link the library to the main executable
target_link_libraries(linear_algebra PRIVATE linear_algebra_lib)

# Add the tests subdirectory
add_subdirectory(tests)

# Enable testing
enable_testing()
