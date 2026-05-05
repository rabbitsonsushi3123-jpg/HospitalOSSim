#pragma once
#include "ResourcePool.h"
#include "Process.h"

class ResourceManager {
public:
    ResourcePool pool;

    bool requestResource(Process* patient, int resourceId);
    void releaseResource(Process* patient);
};
