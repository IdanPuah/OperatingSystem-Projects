
#include "CoEditor.h"

CoEditor::CoEditor(std::shared_ptr<UnBoundedQueue> typeQueuePtr, std::shared_ptr<BoundedBuffer> screenManagerQueuePtr)
    : typeQueue(typeQueuePtr), screenManagerQueue(screenManagerQueuePtr) {
}

void CoEditor::coEditorThread() {
    // Continuously process messages from typeQueue
    while (true) {
        std::string message = typeQueue->remove(); // Blocking call
        // Simulate editing process
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate editing time

        // Check for 'DONE' message
        if (message == "DONE") {
            screenManagerQueue->add("DONE");
            break;
        }

        // Pass edited message to screenManagerQueue
        screenManagerQueue->add(message);
        
    }
}