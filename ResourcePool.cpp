#include "ResourcePool.h"

ResourcePool::ResourcePool() {
    resourceNames = {
        "MRI Scanner",
        "Blood Lab",
        "Operating Room",
        "X-Ray Machine"
    };

    available.resize(resourceNames.size(), true);
}

int ResourcePool::size() const {
    return available.size();
}

std::string ResourcePool::getResourceName(int resourceId) const {
    return resourceNames[resourceId];
}
