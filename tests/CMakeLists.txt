# Include GoogleTest via FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1  # Use the version you prefer
)
FetchContent_MakeAvailable(googletest)

# Function to add a test executable for a single test file
function(add_gtest_executable test_name test_file)
  add_executable(${test_name} ${test_file}) # Create an executable for the test file
  target_link_libraries(${test_name} PRIVATE neural_network_lib gtest gtest_main pthread) # Link dependencies
  add_test(NAME ${test_name} COMMAND ${test_name} --gtest_color=yes --gtest_fail_fast) # Register it as a separate CTest entry
endfunction()

# Enable testing
enable_testing()

# Add separate executables and tests for each test file
add_gtest_executable(MatrixTest test_matrix.cpp)
add_gtest_executable(MatrixOperatorTest test_matrixOperator.cpp)
add_gtest_executable(ThreadPoolTest test_thread-pool.cpp)

