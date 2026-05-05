#include "ResourceManager.h"
#include <iostream>

bool ResourceManager::requestResource(Process* patient, int resourceId) {
    std::string resourceName = pool.getResourceName(resourceId);

    std::cout << "[RESOURCE REQUEST] Patient " << patient->id
              << " (" << patient->name << ") requests "
              << resourceName << "\n";

    if (pool.available[resourceId]) {
        pool.available[resourceId] = false;
        patient->assignResource(resourceId);

        std::cout << "[RESOURCE GRANTED] " << resourceName
                  << " assigned to Patient " << patient->id << "\n";

        return true;
    }

    std::cout << "[RESOURCE DENIED] " << resourceName
              << " is already in use. Patient "
              << patient->id << " must wait.\n";

    return false;
}

void ResourceManager::releaseResource(Process* patient) {
    if (patient->hasResource()) {
        int resourceId = patient->assignedResource;
        std::string resourceName = pool.getResourceName(resourceId);

        pool.available[resourceId] = true;
        patient->releaseResource();

        std::cout << "[RESOURCE RELEASED] Patient " << patient->id
                  << " released " << resourceName << "\n";
    }
}
