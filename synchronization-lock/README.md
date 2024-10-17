# Implementing a Synchronization Lock for File Access

mplement a synchronization lock for file access, ensuring that only one process writes to the file at a time while the others wait.

# Explanation of the Lock Mechanism in the C Code

The locking mechanism in the provided C code uses a simple file-based locking strategy to ensure that only one process at a time can execute the critical section (in this case, the `write_message` function). Here's a breakdown of how it works:

## Key Functions

1. **`acquire_lock()`**:
   * This function attempts to create a lock file named `lockfile.lock`.
   * It uses the `open` system call with the flags `O_CREAT | O_EXCL | O_WRONLY`. This means:
     * `O_CREAT`: Create the file if it does not exist.
     * `O_EXCL`: Ensure that the call fails if the file already exists.
     * `O_WRONLY`: Open the file for writing.
   * If the `open` call fails (returns -1), it indicates that the lock file already exists (meaning another process has acquired the lock).
   * In that case, it sleeps for 1 millisecond (`usleep(1000)`) and then retries to acquire the lock. This loop continues until the lock is successfully acquired.

2. **`release_lock()`**:
   * This function releases the lock by removing the `lockfile.lock` file using the `remove` function.
   * Once this function is called, other processes waiting in `acquire_lock()` can now successfully create the lock file and enter the critical section.

## Critical Section

* The critical section of the code is the `write_message` function, which is responsible for printing a message multiple times with a random delay.
* Each child process (created by `fork`) calls `acquire_lock()` before entering the critical section and `release_lock()` after it completes writing its message. This ensures that messages from different processes do not interleave in the output.

## Overall Process

1. **Forking**: The program forks multiple child processes based on the number of message arguments provided. Each child process attempts to acquire the lock before printing its message.
2. **Locking**: When a child process attempts to print its message, it calls `acquire_lock()`. If the lock is already held by another process, it waits until the lock is available.
3. **Writing**: Once the lock is acquired, the process prints its message.
4. **Releasing the Lock**: After the child process finishes writing, it calls `release_lock()`, allowing other processes to acquire the lock.

## Advantages and Disadvantages

* **Advantages**:
  * Simple to implement and understand.
  * Works across processes since it uses a file as a lock mechanism.

* **Disadvantages**:
  * It relies on the existence of the lock file, which can lead to issues if a process crashes and does not release the lock (the lock file remains).
  * It may not be efficient for a high number of processes due to busy-waiting (the process repeatedly checks for the lock).

This locking mechanism is suitable for simple use cases where coordination between a limited number of processes is required. However, for more complex scenarios, more robust inter-process communication methods may be preferred (like semaphores or mutexes).
