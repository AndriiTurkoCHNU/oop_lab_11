#include <iostream>
#include <thread>
#include "SafeQueue.h"

void producer(SafeQueue<int> &queue) {
    for (int i = 0; i < 30; ++i) {
        queue.enqueue(i);
        std::cout << "Produced: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void consumer(SafeQueue<int> &queue) {
    for (int i = 0; i < 30; ++i) {
        int item = queue.dequeue();
        std::cout << "Consumer : " << item << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

int main() {
    SafeQueue<int> queue(10);

    std::thread producerThread(producer, std::ref(queue));
    std::thread consumerThread(consumer, std::ref(queue));

    producerThread.join();
    consumerThread.join();

    return 0;
}