#include <iostream>
#include <thread>

int counter = 0;

int get_id() {
    std::hash<std::thread::id> hasher;

    return static_cast<int>(hasher(std::this_thread::get_id()));
}

int main() {
    std::thread t1([]() {
        counter += get_id();
        std::cout << "Thread 1 counter: " << counter << std::endl;
    });

    std::thread t2([]() {
        counter += get_id();
        std::cout << "Thread 2 counter: " << counter << std::endl;
    });

    std::thread t3([]() {
        counter += get_id();
        std::cout << "Thread 3 counter: " << counter << std::endl;
    });

    t1.join();
    t2.join();
    t3.join();

    return 0;
}