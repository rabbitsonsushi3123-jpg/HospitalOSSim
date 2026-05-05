#pragma once
#include "Process.h"

class MemoryManager {
private:
    int totalMemory;

public:
    int availableMemory;

    MemoryManager(int totalMemory);

    bool allocate(Process* patient);
    void deallocate(Process* patient);
};
