#include <iostream>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>

std::atomic<bool> countUpComplete(false);
std::mutex mtx;

void countUp() {
    for (int i = 1; i <= 20; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
        std::cout << "Count Up: " << i << std::endl;
    }
    countUpComplete = true; // Signal completion
}

void countDown() {
    // Wait until count up is complete
    while (!countUpComplete) {
        std::this_thread::yield(); // Avoid busy waiting
    }
    for (int i = 20; i >= 0; --i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
        std::cout << "Count Down: " << i << std::endl;
    }
}

int main() {
    std::thread t1(countUp);
    std::thread t2(countDown);

    t1.join();
    t2.join();

    return 0;
}
