#pragma once
#include <string>

class Process {
public:
    int id;
    std::string name;
    int memoryRequired;

    int basePriority;
    int currentPriority;

    int totalTicksNeeded;
    int ticksCompleted;

    int assignedResource;
    int requestedResource;

    bool memoryAllocated;
    bool completed;

    Process(
        int id,
        std::string name,
        int memoryRequired,
        int priority,
        int totalTicksNeeded,
        int requestedResource
    );

    bool hasResource() const;
    void assignResource(int resourceId);
    void releaseResource();

    bool isComplete() const;
    void runOneTick();

    void decayPriority();
    void renewPriority();
};
