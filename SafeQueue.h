#ifndef OOP_LAB_11_SAFEQUEUE_H
#define OOP_LAB_11_SAFEQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class SafeQueue {
private:
    std::queue<T> queue;
    std::mutex m;
    std::condition_variable cv;
    const size_t max_size;
public:
    SafeQueue(size_t max_size) : max_size(max_size) {}

    void enqueue(T item) {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [this]() { return queue.size() < max_size; });
        queue.push(item);
        cv.notify_all();
    }

    T dequeue() {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [this]() { return !queue.empty(); });
        T item = queue.front();
        queue.pop();
        cv.notify_all();
        return item;
    }
};


#endif //OOP_LAB_11_SAFEQUEUE_H
