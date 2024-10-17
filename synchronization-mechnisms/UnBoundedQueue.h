
#ifndef UNBOUNDEDQUEUE_H
#define UNBOUNDEDQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>
#include <memory>

class UnBoundedQueue
{
private:
    std::queue<std::string> queue;
    std::mutex mtx;
    std::condition_variable da;

public:
    UnBoundedQueue () {}
    void add(const std::string& item);
    std::string remove ();
};

#endif