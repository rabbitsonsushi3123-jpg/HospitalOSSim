#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include "ResourcePool.h"

class ResourceManager {
public:
    ResourcePool pool;

    ResourceManager(int count);
    int acquire();
    void release(int id);
};

#endif
