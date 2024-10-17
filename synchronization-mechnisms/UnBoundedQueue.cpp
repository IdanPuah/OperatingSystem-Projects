
#include "UnBoundedQueue.h"

void UnBoundedQueue:: add(const std::string& item) {
        std::unique_lock<std::mutex> lock(mtx);
        queue.push(item);
        da.notify_one(); // Notify waiting threads that data is available
    }

std::string UnBoundedQueue:: remove() {
    std::unique_lock<std::mutex> lock(mtx);
    while (queue.empty()) {
        da.wait(lock); // Wait until data is available
    }
    std::string item = queue.front();
    queue.pop();
    return item;
}