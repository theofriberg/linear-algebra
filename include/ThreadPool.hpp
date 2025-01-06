#pragma once

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

class ThreadPool
{
public:
    /**
     * Constructs a ThreadPool object with the specified number of worker threads.
     * @param pool_size The number of worker threads to create in the pool.
     */
    ThreadPool(size_t pool_size);

    /**
     * Destroys the ThreadPool object and terminates all worker threads.
     */
    ~ThreadPool();

    /**
     * Enqueues a task to be executed by a worker thread in the pool.
     * @param task The task to be executed.
     * @param args The arguments to be passed to the task.
     * @return A future object representing the result of the task.
     */
    template <typename F, typename... Args>
    auto enqueue(F &&task, Args &&...args) -> std::future<decltype(task(args...))>;

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};