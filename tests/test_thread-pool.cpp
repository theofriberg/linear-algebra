#include <gtest/gtest.h>

#include "../include/ThreadPool.hpp"

#include <vector>
#include <future>

TEST(ThreadPoolTest, SingleThread)
{
    ThreadPool threadPool(1);

    int counter = 0;

    auto task = [&counter]()
    { counter++; };

    auto future = threadPool.enqueue(task);
    future.get();

    EXPECT_EQ(counter, 1);
}

TEST(ThreadPoolTest, MultipleThreads)
{
    ThreadPool threadPool(4);

    int counter = 0;

    auto task = [&counter]()
    { counter++; };

    std::vector<std::future<void>> futures;

    for (int i = 0; i < 100; i++)
    {
        futures.push_back(threadPool.enqueue(task));
    }

    for (auto &future : futures)
    {
        future.get();
    }

    EXPECT_EQ(counter, 100);
}

TEST(ThreadPoolTest, ThreadTermination)
{
    ThreadPool thread_pool(4);

    auto future = thread_pool.enqueue([]
                                      { return 42; });

    thread_pool.~ThreadPool();

    EXPECT_EQ(future.get(), 42);
}

TEST(ThreadPoolTest, Concurrency)
{
    ThreadPool thread_pool(4);

    int result = 0;

    std::vector<std::future<void>> futures;

    for (int i = 0; i < 100; i++)
    {
        futures.push_back(thread_pool.enqueue([&result]
                                              {
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Simulate work being done
            result++; }));
    }

    for (auto &future : futures)
    {
        future.get();
    }

    EXPECT_EQ(result, 100);
}

TEST(ThreadPoolTest, EmptyQueue)
{
    ThreadPool thread_pool(4);

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    auto result = thread_pool.enqueue([]
                                      { return 42; });

    EXPECT_EQ(result.get(), 42);
}

TEST(ThreadPoolTest, TestLargeData)
{
    ThreadPool thread_pool(4);

    std::vector<int> large_data(10'000'000, 1);

    auto result_future = thread_pool.enqueue([](std::vector<int> data)
                                             {
        long long sum = 0;
        for(int val : data) {
            sum += val;
        }

        return sum; }, std::move(large_data));

    EXPECT_EQ(result_future.get(), 10'000'000);
}

TEST(ThreadPoolTest, MemoryIntensiveOperation)
{
    ThreadPool thread_pool(4);

    size_t matrix_size = 1000;
    std::vector<std::vector<int>> matrix(matrix_size, std::vector<int>(matrix_size, 1));

    auto result_future = thread_pool.enqueue([matrix_size](std::vector<std::vector<int>> mat)
                                             {
        long long sum = 0;
        for (int i = 0; i < matrix_size; i++) {
            for (int j = 0; j < matrix_size; j++) {
                sum += mat[i][j];
            }
        }

        return sum; }, std::move(matrix));

    EXPECT_EQ(result_future.get(), matrix_size * matrix_size);
}
TEST(ThreadPoolTest, PerformanceTest)
{
    ThreadPool thread_pool(8);

    auto start = std::chrono::high_resolution_clock::now();

    const int num_tasks = 1000;
    std::vector<std::future<long long>> results;

    for (int i = 0; i < num_tasks; ++i)
    {
        results.push_back(thread_pool.enqueue([]()
                                              {
            std::vector<int> largeData(10'000, 1);  // Task with a large data vector
            long long sum = 0;
            for (int val : largeData) {
                sum += val;
            }
            return sum; }));
    }

    long long total_sum = 0;
    for (auto &result : results)
    {
        total_sum += result.get();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Performance test completed in " << duration.count() << " ms. Total sum: " << total_sum << std::endl;

    EXPECT_LT(duration.count(), 5000);
}

TEST(ThreadPoolTest, TestInvalidFunctionThrows)
{
    ThreadPool thread_pool(1);

    char a = '1';
    char b = '2';

    EXPECT_THROW(
        thread_pool.enqueue([](int a, int b)
                            { return a + b; }, std::move(a), std::move(b)),
        std::invalid_argument);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}