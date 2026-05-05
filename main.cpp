#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Logger.h"
#include "MemoryManager.h"
#include "MemoryModel.h"
#include "Process.h"
#include "ResourceManager.h"
#include "ResourcePool.h"
#include "Scheduler.h"

// Global system components
Scheduler scheduler("FCFS");
MemoryManager memoryManager(1024);
ResourceManager resourceManager(3); // R1, R2, R3
Logger logger;

int main() {
    std::srand(std::time(nullptr));

    Logger::log("OS Simulation Started");

    Process* p1 = new Process(1, 4, 120); // needs R1
    Process* p2 = new Process(2, 3, 150); // needs R2
    Process* p3 = new Process(3, 5, 200); // needs R1 (conflict with p1)
    Process* p4 = new Process(4, 2, 100); // needs R3
    Process* p5 = new Process(5, 3, 180); // needs R2 (shared with p2 but different timing)

    std::vector<Process*> processes = {p1, p2, p3, p4, p5};

    // Assign required resources manually (extend Process if needed)
    std::vector<int> requiredResources = {0, 1, 0, 2, 1};

    // Admit all processes
    for (int i = 0; i < processes.size(); i++) {
        Process* p = processes[i];
        Logger::log("Admitted Patient " + std::to_string(p->pid));

        int block = memoryManager.malloc(p->memoryRequired);
        if (block == -1) {
            p->state = WAITING;
            Logger::log("Patient " + std::to_string(p->pid) + " waiting for Operating Room");
        } else {
            p->state = READY;
            scheduler.addProcess(p);
        }
    }

    int time = 0;

    // loop
    while (true) {
        Process* p = scheduler.getNext();
        if (!p) break;

        int resourceNeeded = requiredResources[p->pid - 1];

        Logger::log("[Time " + std::to_string(time) + "] Scheduling Patient " + std::to_string(p->pid));
        p->state = RUNNING;

        // Try to acquire specific resource
        int resource = -1;
        if (resourceManager.pool.resources[resourceNeeded]) {
            resourceManager.pool.resources[resourceNeeded] = false;
            resource = resourceNeeded;
            Logger::log("Patient " + std::to_string(p->pid) + " undergoing MRI" + std::to_string(resource + 1));
        } else {
            Logger::log("Patient " + std::to_string(p->pid) + " waiting for MRI Machine" + std::to_string(resourceNeeded + 1));
            p->state = WAITING;
            scheduler.addProcess(p);
            time++;
            continue;
        }

        // Run one tick
        p->runtime--;
        Logger::log("Patient " + std::to_string(p->pid) + " undergoing procedure (remaining=" + std::to_string(p->runtime) + ")");

        if (p->runtime <= 0) {
            p->state = TERMINATED;
            Logger::log("Patient " + std::to_string(p->pid) + " operation complete");

            resourceManager.pool.resources[resource] = true;
            Logger::log("Patient " + std::to_string(p->pid) + " released from MRI" + std::to_string(resource + 1));

            memoryManager.free(0);

            delete p;
        } else {
            // Release resource after each tick (simplified time-sharing)
            resourceManager.pool.resources[resource] = true;
            scheduler.addProcess(p);
        }

        time++;
    }

    return 0;
}
