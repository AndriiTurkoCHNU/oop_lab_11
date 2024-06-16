#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;
std::mutex m;

int get_id() {
    std::hash<std::thread::id> hasher;

    return static_cast<int>(hasher(std::this_thread::get_id()));
}

int main() {
    std::thread t1([]() {
        m.lock();
        counter += get_id();
        std::cout << "Thread 1 counter: " << counter << std::endl;
        m.unlock();
    });

    std::thread t2([]() {
        m.lock();
        counter += get_id();
        std::cout << "Thread 2 counter: " << counter << std::endl;
        m.unlock();
    });

    std::thread t3([]() {
        m.lock();
        counter += get_id();
        std::cout << "Thread 3 counter: " << counter << std::endl;
        m.unlock();
    });

    t1.join();
    t2.join();
    t3.join();

    return 0;
}