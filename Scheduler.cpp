
#include "Scheduler.h"
#include "Logger.h"

Scheduler::Scheduler(std::string p) : policy(p) {}

void Scheduler::addProcess(Process* p) {
    p->state = READY;
    readyQueue.push(p);
    Logger::log("Process added to queue");
}

Process* Scheduler::getNext() {
    if (readyQueue.empty()) return nullptr;

    Process* p = readyQueue.front();
    readyQueue.pop();
    return p;
}
