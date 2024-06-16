#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1, m2;

void thread1() {
    m1.lock();
    std::cout << "Thread 1 locked m1\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Thread 1 waiting for m2 unlock\n";
    m2.lock();
    std::cout << "Thread 1 locked m2\n";
    m2.unlock();
    m1.unlock();
}

void thread2() {
    m2.lock();
    std::cout << "Thread 2 locked m2\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Thread 2 waiting for m1 unlock\n";
    m1.lock();
    std::cout << "Thread 2 locked m1\n";
    m1.unlock();
    m2.unlock();
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}