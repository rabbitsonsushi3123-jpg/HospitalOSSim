#include "ResourcePool.h"

ResourcePool::ResourcePool(int count) {
    resources.resize(count, true);
}
