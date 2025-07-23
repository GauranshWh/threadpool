#include "thread.hpp"
#include <iostream>
#include <chrono>
#include <mutex>

std::mutex cout_mutex;

int main() {
    ThreadPool pool(4, 1000);
    const int num_tasks = 400;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_tasks; ++i) {
        pool.enqueue([i] {
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout << "Task " << i << " executed by thread "
                          << std::this_thread::get_id() << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        });
    }

    pool.shutdown();

    //Total time taken
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Completed " << num_tasks << " tasks in "
                  << duration.count() << " seconds" << std::endl;
    }

    return 0;
}
