
#ifndef BOUNDEDBUFFER_H
#define BOUNDEDBUFFER_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>
#include <memory>

class BoundedBuffer {
private:
    size_t maxSize;
    std::queue<std::string> buffer;
    std::mutex mtx;
    std::condition_variable notFull;
    std::condition_variable notEmpty;

public:
    BoundedBuffer(size_t size) : maxSize(size) {}

    void add(const std::string& item);
    std::string remove();
};

#endif // BOUNDEDBUFFER_H
