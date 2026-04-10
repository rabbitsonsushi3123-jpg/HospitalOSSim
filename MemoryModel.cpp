#include "MemoryModel.h"
#include "Logger.h"

MemoryModel::MemoryModel(int totalSize) {
    blocks.push_back({totalSize, true});
}

int MemoryModel::allocate(int size) {
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i].free && blocks[i].size >= size) {
            Logger::log("Allocating memory");

            if (blocks[i].size > size) {
                blocks.insert(blocks.begin() + i + 1,
                              {blocks[i].size - size, true});
            }

            blocks[i].size = size;
            blocks[i].free = false;
            return i;
        }
    }
    return -1;
}

void MemoryModel::freeBlock(int index) {
    if (index >= 0 && index < blocks.size()) {
        blocks[index].free = true;
        Logger::log("Memory freed");
    }
}
