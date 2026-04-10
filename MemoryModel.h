#ifndef MEMORYMODEL_H
#define MEMORYMODEL_H
#include <vector>

struct Block {
    int size;
    bool free;
};

class MemoryModel {
public:
    std::vector<Block> blocks;

    MemoryModel(int totalSize);
    int allocate(int size);
    void freeBlock(int index);
};

#endif
