#include "MemoryManager.h"
#include <iostream>

MemoryManager::MemoryManager(int totalMemory)
    : totalMemory(totalMemory), availableMemory(totalMemory) {}

bool MemoryManager::allocate(Process* patient) {
    std::cout << "[MEMORY REQUEST] Patient " << patient->id
              << " needs " << patient->memoryRequired << " units\n";

    if (availableMemory >= patient->memoryRequired) {
        availableMemory -= patient->memoryRequired;
        patient->memoryAllocated = true;

        std::cout << "[MEMORY GRANTED] Patient " << patient->id
                  << " allocated " << patient->memoryRequired
                  << " units | Memory left: "
                  << availableMemory << "\n";

        return true;
    }

    std::cout << "[MEMORY DENIED] Not enough memory for Patient "
              << patient->id << " | Needed: "
              << patient->memoryRequired
              << " | Available: " << availableMemory << "\n";

    return false;
}

void MemoryManager::deallocate(Process* patient) {
    if (patient->memoryAllocated) {
        availableMemory += patient->memoryRequired;
        patient->memoryAllocated = false;

        std::cout << "[MEMORY RELEASED] Patient " << patient->id
                  << " freed " << patient->memoryRequired
                  << " units | Memory left: "
                  << availableMemory << "\n";
    }
}
