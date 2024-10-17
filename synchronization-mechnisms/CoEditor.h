
#ifndef COEDITOR_H
#define COEDITOR_H

#include "BoundedBuffer.h"
#include "UnBoundedQueue.h"
#include <memory>
#include <thread>
#include <chrono>

class CoEditor {
private:
    std::shared_ptr<UnBoundedQueue> typeQueue;
    std::shared_ptr<BoundedBuffer> screenManagerQueue;

public:
    CoEditor(std::shared_ptr<UnBoundedQueue> typeQueuePtr, std::shared_ptr<BoundedBuffer> screenManagerQueuePtr);

    // Method to simulate editing and passing messages to screen manager
    void coEditorThread();    
};

#endif