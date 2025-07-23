#include "thread.hpp"
#include <iostream>
#include <chrono>
#include <mutex>

std::mutex cout_mutex;


int main(){
    ThreadPool pool(5,500);

    for(int i = 0 ; i < 400 ;++i){
        pool.enqueue([i]{
            {
                std::lock_guard<std::mutex> lock(cout_mutex);
                std::cout<< " Tast" << i << "executed by thread" << std::this_thread::get_id()<<std::endl;
            }
           
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

        });

    }

    std:: this_thread::sleep_for(std::chrono::seconds(2));
    pool.shutdown();

    return 0;
}