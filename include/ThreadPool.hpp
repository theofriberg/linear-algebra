#pragma once

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

class ThreadPool
{
public:
    ThreadPool(size_t pool_size);
    ~ThreadPool();
    template <typename F>
    void enqueue(F &&task);

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;
};