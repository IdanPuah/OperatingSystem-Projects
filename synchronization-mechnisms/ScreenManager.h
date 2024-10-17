
#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "BoundedBuffer.h"
#include <memory>

class ScreenManager
{
private:
    int doneCounter;
    std::shared_ptr<BoundedBuffer> screenManagerQueue;

public:
    ScreenManager(std::shared_ptr<BoundedBuffer> screenManagerQueuePtr);

    void screenManagerThread(); 
    
};

#endif

