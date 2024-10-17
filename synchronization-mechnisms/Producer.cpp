
#include "Producer.h"
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <random>

// Constructor for Producer
Producer::Producer(int id, int numProducts, int queueSize, std::shared_ptr<BoundedBuffer> queue)
    : id(id), numProducts(numProducts), queueSize(queueSize), queue(queue) {
    // Constructor implementation
}

// Private method to generate a story
std::string Producer::generateStory(int count, const std::string& type) {
        std::ostringstream story;
        story << "Producer " << id << " " << type << " " << count;
        return story.str();
    }

// Method to simulate the producer's work
void Producer::producerThread() {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<std::string> storyTypes = {"SPORTS", "NEWS", "HEALTH"};
    std::uniform_int_distribution<> dis(0, storyTypes.size() - 1);

    for (int i = 0; i < numProducts; ++i) {
        // Randomly select a type from storyTypes
        int idx = dis(gen);
        std::string type = storyTypes[idx];

        // Generate story based on the selected type
        std::string story;
        if (type == "SPORTS") {
            story = generateStory(sportNum, type);
            sportNum++; 
        } else if (type == "NEWS") {
            story = generateStory(newsNum, type); 
            newsNum++;
        } else if (type == "HEALTH") {
            story = generateStory(healthNum, type); 
            healthNum++;
        }

        // Produce the story (enqueue it)
        queue->add(story);

        // Simulate time delay for producing stories
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    queue->add("DONE");
}
