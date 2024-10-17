
#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <vector>
#include "Producer.h"
#include "UnBoundedQueue.h"
#include <memory>
#include <sstream>

class Dispatcher {
private:
    std::vector<std::shared_ptr<Producer>> allProducers;
    std::shared_ptr<UnBoundedQueue> queueSport;
    std::shared_ptr<UnBoundedQueue> queueNews;
    std::shared_ptr<UnBoundedQueue> queueWeather;

public:
    // Constructor to initialize the Dispatcher with UnBoundedQueue references
     Dispatcher(std::shared_ptr<UnBoundedQueue> queueSport, std::shared_ptr<UnBoundedQueue> queueNews, std::shared_ptr<UnBoundedQueue> queueWeather);

    // Method to add a producer to the vector
    void addProducer(std::shared_ptr<Producer> producer);

    // Method to access all producers
    const std::vector<std::shared_ptr<Producer>> getProducers() const;

    void dispatcherThread ();
};

#endif // DISPATCHER_H
