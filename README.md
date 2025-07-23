Custom Thread Pool in Modern C++

A lightweight and efficient thread pool designed to manage and optimize concurrent task execution using a fixed set of reusable worker threads.

Features

- Fixed-size thread pool with configurable thread count
-  Task queue with max capacity control
-  Thread-safe using  std::mutex  and  std::condition_variable 
-  Graceful shutdown ( shutdown() and  shutdown_now() )
-  Exception-safe task execution
-  Simple task submission using lambdas or function objects

---

Project Structure

-  thread.hpp  – ThreadPool class definition and implementation
-  main.cpp  – Usage demo: enqueues 400 tasks into a 5-thread pool
- Thread-safe logging using `std::mutex` for `std::cout`
- Built-in backoff: limits queue capacity to prevent overload

---

Example Usage

cpp
#include "thread.hpp"
#include <iostream>

int main() {
    ThreadPool pool(5, 500); // 5 worker threads, 500 task capacity

    for (int i = 0; i < 400; ++i) {
        pool.enqueue([i] {
            std::cout << "Task " << i << " executed by thread "
                      << std::this_thread::get_id() << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));
    pool.shutdown();
    return 0;
}

build and run

g++ -std=c++17 main_t.cpp -pthread -o thread
./thread



Next will be building custom threadpool with work stealing
NUMA-aware task scheduler for compute-bound workloads.
from which we can
Achieve 3x faster task dispatch compared to naive multithreading.
