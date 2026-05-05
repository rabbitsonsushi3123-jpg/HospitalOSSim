#include "Process.h"

Process::Process(
    int id,
    std::string name,
    int memoryRequired,
    int priority,
    int totalTicksNeeded,
    int requestedResource
)
    : id(id),
      name(name),
      memoryRequired(memoryRequired),
      basePriority(priority),
      currentPriority(priority),
      totalTicksNeeded(totalTicksNeeded),
      ticksCompleted(0),
      assignedResource(-1),
      requestedResource(requestedResource),
      memoryAllocated(false),
      completed(false) {}

bool Process::hasResource() const {
    return assignedResource != -1;
}

void Process::assignResource(int resourceId) {
    assignedResource = resourceId;
}

void Process::releaseResource() {
    assignedResource = -1;
}

bool Process::isComplete() const {
    return ticksCompleted >= totalTicksNeeded;
}

void Process::runOneTick() {
    ticksCompleted++;

    if (isComplete()) {
        completed = true;
    }
}

void Process::decayPriority() {
    if (currentPriority > 1) {
        currentPriority--;
    }
}

void Process::renewPriority() {
    currentPriority = basePriority;
}
