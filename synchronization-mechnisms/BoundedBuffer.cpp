
#include "BoundedBuffer.h"

// Add an item to the buffer
void BoundedBuffer::add(const std::string& item) {
    std::unique_lock<std::mutex> lock(mtx);
    notFull.wait(lock, [this] { return buffer.size() < maxSize; });
    buffer.push(item);
    notEmpty.notify_one();
}

// Remove an item from the buffer
std::string BoundedBuffer::remove() {
    std::unique_lock<std::mutex> lock(mtx);
    notEmpty.wait(lock, [this] { return !buffer.empty(); });
    std::string item = buffer.front();
    buffer.pop();
    notFull.notify_one();
    return item;
};
