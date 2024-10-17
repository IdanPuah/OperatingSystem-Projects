
#include "Dispatcher.h"
#include "Producer.h"
#include "BoundedBuffer.h"
#include <iostream>
#include "UnBoundedQueue.h"

Dispatcher::Dispatcher(std::shared_ptr<UnBoundedQueue> queueSport, std::shared_ptr<UnBoundedQueue> queueNews, std::shared_ptr<UnBoundedQueue> queueWeather)
    : queueSport(queueSport), queueNews(queueNews), queueWeather(queueWeather) {}


// Method to add a producer to the vector
void Dispatcher::addProducer(std::shared_ptr<Producer> producer)
{
    allProducers.push_back(producer);
}

// Method to access all producers
const std::vector<std::shared_ptr<Producer>>Dispatcher::getProducers() const
{
    return allProducers;
}

void Dispatcher::dispatcherThread()
{
    // continue till all producers done
    size_t i = 0;
    while (!allProducers.empty())
    {
        if (i == (allProducers.size()))
        {
            i = 0;
        }

        // std::cout << "i: " << i << std::endl;

        // get element from producer
        std::shared_ptr<BoundedBuffer> queuePtr = allProducers[i]->getQueue();
        std::string item = queuePtr->remove();

        if (item == "DONE") // Remove the producer from allProducers in case its done
        {
            allProducers.erase(allProducers.begin() + i);
            continue;
        }

        // Parse the item to determine its type
        std::istringstream iss(item);
        std::string producer;
        int producerNumber;
        std::string type;
        int typeNumber;

        iss >> producer >> producerNumber >> type >> typeNumber;

        // Determine which queue to add the item to based on type using switch case
        // move to appropriate co-editor queue
        if (type == "SPORTS")
        {
            queueSport->add(item);
        }
        else if (type == "NEWS")
        {
            queueNews->add(item);
        }
        else if (type == "HEALTH")
        {
            queueWeather->add(item);
        }
        else
        {
            std::cerr << "Unknown type: " << type << ". Item ignored." << std::endl;
            // Handle unknown type if needed
        }

        i++; // Move to the next producer
    }
    queueSport->add("DONE");
    queueNews->add("DONE");
    queueWeather->add("DONE");
};
