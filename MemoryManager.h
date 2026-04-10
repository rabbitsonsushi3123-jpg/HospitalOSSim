#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#include "MemoryModel.h"

class MemoryManager {
public:
    MemoryModel memory;

    MemoryManager(int size);
    int malloc(int size);
    void free(int index);
};

#endif
