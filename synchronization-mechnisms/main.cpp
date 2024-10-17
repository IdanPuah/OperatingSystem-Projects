
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include "BoundedBuffer.h"
#include "Producer.h"
#include "Dispatcher.h"
#include "UnBoundedQueue.h"
#include "CoEditor.h"
#include "ScreenManager.h"

namespace std {
    template<typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}

int parseFile(const std::string& fileName, std::vector<std::shared_ptr<Producer>>& allProducers, std::vector<std::unique_ptr<BoundedBuffer>>& allBuffers, int& coEditorQueueSize){
    // open config file
    std::ifstream configFile(fileName);
    if (!configFile) {
        std::cerr << "Error opening config file " << fileName << std::endl;
        return -1;
    }

    std::string line;
    std::string type;

    int numProducts = 0;
    size_t queueSize = 0;
    int producerIndex = 0;

    // Read each line from the configuration file
    while (std::getline(configFile, line)) {
        std::istringstream iss(line);  // Create a stringstream to parse the line

        // Check if the line contains "PRODUCER"
        if (line.find("PRODUCER") != std::string::npos) {
            producerIndex++; // Increment producer index for each PRODUCER line

            // Read the number of products (assuming it's on the next line)
            std::getline(configFile, line);
            std::istringstream numProductsIss(line);
            numProductsIss >> numProducts;

            // Read the queue size line
            std::getline(configFile, line);
            std::istringstream queueSizeIss(line);
            queueSizeIss.ignore(256, '='); // Skip until '='
            queueSizeIss >> queueSize;


            // Create a BoundedBuffer for the queue
            std::shared_ptr<BoundedBuffer> buffer = std::make_shared<BoundedBuffer>(queueSize);
            // allBuffers.push_back(std::move(buffer));

            // Add a new Producer object to the vector with the current producerIndex
            auto producer = std::make_shared<Producer>(producerIndex, numProducts, queueSize, buffer);
            allProducers.push_back(producer);
            
        }

        // Check if the line contains "Co-Editor queue size"
        else if (line.find("Co-Editor queue size") != std::string::npos) {
            std::istringstream coEditorIss(line);
            coEditorIss.ignore(256, '='); // Skip until '='
            coEditorIss >> coEditorQueueSize;  // Read co-editor queue size
        }
    }


    configFile.close();
    return 0;
}


int main(int argc, char *argv[]){
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <config file>" << std::endl;
        return 1;
    }

    std::vector<std::shared_ptr<Producer>> allProducers;
    std::vector<std::unique_ptr<BoundedBuffer>> allBuffers;
    // int producerNum = 0;
    int coEditorQueueSize = 0;

    // parse the file
    if (parseFile(argv[1], allProducers, allBuffers, coEditorQueueSize) != 0){
        std::cerr << "Error parsing configuration file " << argv[1] << std::endl;
        return 1;
    }

    // Create UnBoundedQueue objects for sports, news, and weather
    auto queueSport = std::make_shared<UnBoundedQueue>();
    auto queueNews = std::make_shared<UnBoundedQueue>();
    auto queueWeather = std::make_shared<UnBoundedQueue>();

    // Initialize dispatcher with the UnBoundedQueue objects
    auto dispatcher = std::make_shared<Dispatcher>(queueSport, queueNews, queueWeather);

    // add producers to the dispatcher
    for (auto& producer : allProducers) {
        dispatcher->addProducer(producer);
    }

    // initial the screenManager queue
    auto screenManagerQueue = std::make_shared<BoundedBuffer>(coEditorQueueSize);

    // initial coEditors
   auto sportCoEditor = std::make_shared<CoEditor>(queueSport, screenManagerQueue);
   auto newsCoEditor = std::make_shared<CoEditor>(queueNews, screenManagerQueue);
   auto healthCoEditor = std::make_shared<CoEditor>(queueWeather, screenManagerQueue);

    //initial screen manager instance
    auto screenManager = std::make_shared<ScreenManager>(screenManagerQueue);

    // // Print out information from all producers in dispatcher
    // for (const auto& producer : dispatcher->getProducers()) {
    //     std::cout << "Producer ID: " << producer->getId() << std::endl;
    //     std::cout << "  Number of Products: " << producer->getNumProducts() << std::endl;
    //     std::cout << "  Queue Size: " << producer->getQueueSize() << std::endl;
    // }
    // std::cout << "Co-Editor queue size: " << coEditorQueueSize << std::endl;
    // std::cout << "all producers size: " << allProducers.size() << std::endl;

    // start the threads
    std::vector<std::thread> threads;

    for (const auto& producer : allProducers) {
        threads.emplace_back(&Producer::producerThread, producer);
    }

    threads.emplace_back(&Dispatcher::dispatcherThread, dispatcher);
    threads.emplace_back(&CoEditor::coEditorThread, sportCoEditor);
    threads.emplace_back(&CoEditor::coEditorThread, newsCoEditor);
    threads.emplace_back(&CoEditor::coEditorThread, healthCoEditor);
    threads.emplace_back(&ScreenManager::screenManagerThread, screenManager);

    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }


    return 0;
}