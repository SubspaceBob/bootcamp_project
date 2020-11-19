#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H
#include <iostream>
#include <mutex>
#include <shared_mutex>


template <typename T>
struct SharedMemory
{
    std::shared_mutex mutex;
    T memory;

    void write(const T& frame)
    {
        std::unique_lock lock(mutex);
        memory.write(frame);
    }

    T read()
    {
        std::shared_lock lock(mutex);

        return memory;
    }
};

#endif
