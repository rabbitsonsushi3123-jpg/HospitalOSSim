#ifndef RESOURCEPOOL_H
#define RESOURCEPOOL_H
#include <vector>

class ResourcePool {
public:
    std::vector<bool> resources;

    ResourcePool(int count);
};

#endif
