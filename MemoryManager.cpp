#include "MemoryManager.h"

MemoryManager::MemoryManager(int size) : memory(size) {}

int MemoryManager::malloc(int size) {
    return memory.allocate(size);
}

void MemoryManager::free(int index) {
    memory.freeBlock(index);
}
