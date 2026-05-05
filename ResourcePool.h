#pragma once
#include <vector>
#include <string>

class ResourcePool {
public:
    std::vector<bool> available;
    std::vector<std::string> resourceNames;

    ResourcePool();

    int size() const;
    std::string getResourceName(int resourceId) const;
};
