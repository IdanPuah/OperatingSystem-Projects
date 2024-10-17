
#include "ScreenManager.h"
#include <iostream>
#include <chrono> 
#include <thread> 

// Constructor definition
ScreenManager::ScreenManager(std::shared_ptr<BoundedBuffer> screenManagerQueuePtr)
    : doneCounter(0), screenManagerQueue(screenManagerQueuePtr) {
}

void ScreenManager::screenManagerThread(){
    while (doneCounter < 3){
        std::string item = screenManagerQueue->remove();

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate editing time

        if (item == "DONE"){
            doneCounter++;
            continue;
        }

       std::cout << item << std::endl;
    }
    std::cout << "DONE" << std::endl;
}