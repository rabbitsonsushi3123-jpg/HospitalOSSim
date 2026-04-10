#include "ResourceManager.h"
#include "Logger.h"

ResourceManager::ResourceManager(int count) : pool(count) {}

int ResourceManager::acquire() {
    for (int i = 0; i < pool.resources.size(); i++) {
        if (pool.resources[i]) {
            pool.resources[i] = false;
            Logger::log("Resource acquired");
            return i;
        }
    }
    return -1;
}

void ResourceManager::release(int id) {
    if (id >= 0 && id < pool.resources.size()) {
        pool.resources[id] = true;
        Logger::log("Resource released");
    }
}
