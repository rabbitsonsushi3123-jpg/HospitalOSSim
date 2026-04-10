#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <queue>
#include <string>
#include "Process.h"

class Scheduler {
public:
    std::string policy;
    std::queue<Process*> readyQueue;

    Scheduler(std::string p);
    void addProcess(Process* p);
    Process* getNext();
};

#endif
