#include <gtest/gtest.h>

#include "../include/ThreadPool.hpp"

#include <future>
#include <chrono>
#include <vector>
#include <atomic>

TEST(ThreadPoolTest, SingleTaskExecution)
{
    ThreadPool thread_pool(2);
    std::atomic<int> counter{0};

    auto task = [&counter]()
    {
        counter.fetch_add(1, std::memory_order_relaxed);
    };

    thread_pool.enqueue(task);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    EXPECT_EQ(counter.load(), 1);
}

TEST(ThreadPoolTest, MultipleTaskExecution)
{
    ThreadPool thread_pool(4);
    int num_tasks = 10;

    std::vector<std::future<int>> futures;
    for (int i = 0; i < num_tasks; ++i)
    {
        futures.emplace_back(thread_pool.enqueue([]
                                                 { return 42; }));
    }

    for (auto &future : futures)
    {
        int val = future.get();
        EXPECT_EQ(val, 42);
    }
}

TEST(ThreadPoolTest, ParallellExecution)
{
    ThreadPool thread_pool(4);
    std::vector<std::future<void>> futures;
    std::atomic<int> counter{0};
    const int num_tasks = 4;

    for (int i = 0; i < num_tasks; ++i)
    {
        futures.emplace_back(thread_pool.enqueue([&counter]()
                                                 {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            counter.fetch_add(1, std::memory_order_relaxed); }));
    }

    for (auto &future : futures)
    {
        future.get();
    }

    EXPECT_EQ(counter.load(), num_tasks);
}

TEST(ThreadPoolTest, TestDestruction)
{
    std::atomic<int> counter{0};

    {
        ThreadPool thread_pool(2);

        for (int i = 0; i < 5; ++i)
        {
            thread_pool.enqueue([&counter]()
                                {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                counter.fetch_add(1, std::memory_order_relaxed); });
        }
    }

    EXPECT_EQ(counter.load(), 5);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}