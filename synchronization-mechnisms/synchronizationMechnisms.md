# Concurrent Programming and Synchronization Mechanisms Assignment

This project implements a producer-consumer model using multiple threads to simulate a news story generation and editing system. Producers generate news stories of different types (sports, news, health) and add them to bounded and unbounded queues. CoEditors process these stories, and a Dispatcher routes them to the appropriate queues based on their type. A ScreenManager then manages the output of processed stories. The architecture facilitates concurrent processing, ensuring efficient resource utilization.


# Class Descriptions

## BoundedBuffer
The `BoundedBuffer` class implements a thread-safe bounded buffer (FIFO queue) that allows for the storage of a limited number of items. It uses a mutex for synchronization and condition variables to manage access to the buffer.

### Methods
- `void add(const std::string& item)`: Adds an item to the buffer, blocking if the buffer is full until space is available.
- `std::string remove()`: Removes and returns an item from the buffer, blocking if the buffer is empty until an item is available.

---

## CoEditor
The `CoEditor` class represents a co-editor that processes messages from a type queue. It simulates the editing process and passes edited messages to a screen manager queue.

### Constructor
- `CoEditor(std::shared_ptr<UnBoundedQueue> typeQueuePtr, std::shared_ptr<BoundedBuffer> screenManagerQueuePtr)`: Initializes the `CoEditor` with pointers to the type queue and screen manager queue.

### Methods
- `void coEditorThread()`: Continuously processes messages from the type queue, simulating an editing process. It adds the edited message to the screen manager queue and checks for a "DONE" message to terminate the thread.

---

## Dispatcher
The `Dispatcher` class manages multiple producers and routes their messages to appropriate queues based on the message type. It operates in a round-robin fashion to process items from each producer.

### Constructor
- `Dispatcher(std::shared_ptr<UnBoundedQueue> queueSport, std::shared_ptr<UnBoundedQueue> queueNews, std::shared_ptr<UnBoundedQueue> queueWeather)`: Initializes the dispatcher with shared pointers to the sports, news, and weather queues.

### Methods
- `void addProducer(std::shared_ptr<Producer> producer)`: Adds a producer to the dispatcher.
- `const std::vector<std::shared_ptr<Producer>> getProducers() const`: Returns all producers managed by the dispatcher.
- `void dispatcherThread()`: Processes messages from producers in a round-robin manner and routes them to the appropriate queues based on the message type.

---

## Producer
The `Producer` class generates stories and adds them to a bounded buffer. It simulates production work by randomly selecting a story type and generating a corresponding message.

### Constructor
- `Producer(int id, int numProducts, int queueSize, std::shared_ptr<BoundedBuffer> queue)`: Initializes the producer with an ID, number of products to generate, queue size, and a pointer to the bounded buffer.

### Methods
- `std::string generateStory(int count, const std::string& type)`: Generates a formatted story string based on the producer ID, type, and count.
- `void producerThread()`: Simulates the producer's work by generating and adding stories to the buffer, with a random delay between productions. It adds a "DONE" message to indicate completion.

---

## ScreenManager
The `ScreenManager` class consumes messages from a screen manager queue and simulates the display of these messages. It tracks completion of its tasks with a counter.

### Constructor
- `ScreenManager(std::shared_ptr<BoundedBuffer> screenManagerQueuePtr)`: Initializes the screen manager with a pointer to the screen manager queue.

### Methods
- `void screenManagerThread()`: Continuously removes messages from the queue and simulates processing them. It increments a counter when a "DONE" message is received, terminating when three "DONE" messages have been processed.

---

## UnBoundedQueue
The `UnBoundedQueue` class implements a thread-safe unbounded queue that allows for the addition and removal of items without size restrictions. It uses a mutex for synchronization.

### Methods
- `void add(const std::string& item)`: Adds an item to the queue, notifying any waiting threads that data is available.
- `std::string remove()`: Removes and returns an item from the queue, blocking if the queue is empty until an item is available.

