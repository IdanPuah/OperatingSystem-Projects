
#ifndef PRODUCER_H
#define PRODUCER_H

#include <string>
#include <vector>
#include "BoundedBuffer.h"
#include <memory>

class Producer {
private:
    int id;
    int numProducts;
    int sportNum;
    int newsNum;
    int healthNum;
    int queueSize;
   std::shared_ptr<BoundedBuffer> queue;

    std::string generateStory(int count, const std::string &type);

public:
    Producer(int id, int numProducts, int queueSize, std::shared_ptr<BoundedBuffer> queue);
    int getId() const { return id; }
    int getNumProducts() const { return numProducts; }
    int getQueueSize() const { return queueSize; }
     std::shared_ptr<BoundedBuffer> getQueue(){ return queue; }
    void producerThread();
};

#endif // PRODUCER_H
