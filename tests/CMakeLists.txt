# Include GoogleTest via FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1  # Use the version you prefer
)
FetchContent_MakeAvailable(googletest)

# Define the test executable
add_executable(run_tests test_matrix.cpp test_matrixOperator.cpp test_thread-pool.cpp)

# Link the library and GoogleTest to the test executable
target_link_libraries(run_tests PRIVATE neural_network_lib gtest gtest_main pthread)

# Enable testing with CTest
add_test(NAME MatrixTest COMMAND run_tests)
add_test(NAME MatrixOperatorTest COMMAND run_tests)
add_test(NAME ThreadPoolTest COMMAND run_tests)

enable_testing()

