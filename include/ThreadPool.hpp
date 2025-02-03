#pragma once

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>

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
     * @brief Enqueues a task to be executed by a worker thread.
     *
     * @param task The task to be executed.
     * @return std::future<decltype(task(args...))> A future object that can be used to retrieve the result of the task.
     *
     * The enqueue method adds a task to the task queue and returns a future object that can be used to retrieve the result of the task.
     * The task is wrapped in a packaged_task object, which is stored in a shared pointer to ensure that the task is not destroyed
     * before it is executed. The task is added to the queue using a lambda function that calls the packaged_task object. The return
     * type of the task is deduced using decltype and passed to the std::future object, which is returned to the caller.
     */
    template <typename F, typename... Args>
    auto enqueue(F &&task, Args &&...args) -> std::future<decltype(task(args...))>
    {
        using return_type = decltype(task(args...));

        if constexpr (!std::is_invocable_v<F, Args...>)
        {
            throw std::invalid_argument("Invalid arguments");
        }

        auto wrapper = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(task), std::forward<Args>(args)...));

        std::future<return_type> future = wrapper->get_future();

        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            tasks.emplace([wrapper]()
                          { (*wrapper)(); });
        }

        return future;
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};