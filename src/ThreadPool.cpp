#include "../include/ThreadPool.hpp"

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>

/**
 * @brief Constructs a ThreadPool object with the specified number of worker threads.
 *
 * @param pool_size The number of worker threads to create in the pool.
 *
 * The ThreadPool constructor initializes the stop flag to false and creates the specified number of worker threads.
 * Each worker thread is responsible for executing tasks from the task queue. The worker threads continuously wait for tasks
 * to be added to the queue using a condition variable. Once a task is available, the worker thread locks the queue mutex,
 * pops the task from the queue, unlocks the mutex, and executes the task. The worker threads continue to run until the stop
 * flag is set to true and the task queue is empty.
 */
ThreadPool::ThreadPool(size_t pool_size)
    : stop(false)
{
    for (size_t i = 0; i < pool_size; i++)
    {
        workers.emplace_back([this]
                             {
            while (true)
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                condition.wait(lock, [this] {
                    return stop || !tasks.empty();
                });
                if (stop && tasks.empty())
                    return;

                auto task = std::move(tasks.front());
                tasks.pop();
                lock.unlock();
                task();
            } });
    }
}

/**
 * @brief Destroys the ThreadPool object and terminates all worker threads.
 *
 * The destructor sets the stop flag to true, notifies all waiting worker threads, and waits for each worker thread to finish.
 * This ensures that all tasks in the queue are executed before the ThreadPool object is destroyed.
 */
ThreadPool::~ThreadPool()
{
    std::unique_lock<std::mutex> lock(queue_mutex);
    stop = true;
    lock.unlock();
    condition.notify_all();
    for (auto &worker : workers)
        worker.join();
}

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
auto ThreadPool::enqueue(F &&task, Args &&...args) -> std::future<decltype(task(args...))>
{
    using return_type = decltype(task(args...));

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