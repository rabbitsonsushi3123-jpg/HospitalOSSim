#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

#include "Process.h"
#include "Scheduler.h"
#include "MemoryManager.h"
#include "ResourceManager.h"

void tryMovePatientsFromMemoryWaitQueue(
    std::queue<Process*>& memoryWaitQueue,
    Scheduler& scheduler,
    MemoryManager& memoryManager
) {
    int queueSize = memoryWaitQueue.size();

    for (int i = 0; i < queueSize; i++) {
        Process* patient = memoryWaitQueue.front();
        memoryWaitQueue.pop();

        std::cout << "[MEMORY WAIT CHECK] Checking Patient "
                  << patient->id << "\n";

        if (memoryManager.allocate(patient)) {
            std::cout << "[MOVED TO READY QUEUE] Patient "
                      << patient->id << " now has memory\n";
            scheduler.addPatient(patient);
        } else {
            std::cout << "[STAYS IN MEMORY WAIT QUEUE] Patient "
                      << patient->id << "\n";
            memoryWaitQueue.push(patient);
        }
    }
}

void renewAllPriorities(std::vector<Process*>& patients) {
    std::cout << "[PRIORITY RENEWAL] 5 ticks passed. Renewing all patient priorities.\n";

    for (Process* patient : patients) {
        if (!patient->completed) {
            patient->renewPriority();

            std::cout << "[PRIORITY RENEWED] Patient "
                      << patient->id
                      << " priority restored to "
                      << patient->currentPriority << "\n";
        }
    }
}

int main() {
    std::string schedulingMode;

    std::cout << "Choose scheduling mode: RR or FCFS: ";
    std::cin >> schedulingMode;

    if (schedulingMode != "RR" && schedulingMode != "FCFS") {
        std::cout << "Invalid mode. Defaulting to FCFS.\n";
        schedulingMode = "FCFS";
    }

    std::cout << "\n[SIMULATION STARTED] Mode: "
              << schedulingMode << "\n\n";

    Scheduler scheduler;
    MemoryManager memoryManager(1024);
    ResourceManager resourceManager;

    std::queue<Process*> memoryWaitQueue;
    std::queue<Process*> resourceWaitQueue;

    std::vector<Process*> patients = {
        new Process(1, "Patient A", 300, 5, 3, 0), // MRI Scanner
        new Process(2, "Patient B", 300, 4, 2, 0), // MRI Scanner, causes denial
        new Process(3, "Patient C", 600, 3, 2, 2), // Operating Room
        new Process(4, "Patient D", 500, 2, 2, 3), // X-Ray Machine
        new Process(5, "Patient E", 700, 1, 2, 1)  // Blood Lab, memory wait likely
    };

    for (Process* patient : patients) {
        std::cout << "[NEW PATIENT] Patient " << patient->id
                  << " (" << patient->name << ")"
                  << " | Memory: " << patient->memoryRequired
                  << " | Priority: " << patient->currentPriority
                  << " | Needs: "
                  << resourceManager.pool.getResourceName(patient->requestedResource)
                  << "\n";

        if (memoryManager.allocate(patient)) {
            scheduler.addPatient(patient);
        } else {
            std::cout << "[ADDED TO MEMORY WAIT QUEUE] Patient "
                      << patient->id << "\n";
            memoryWaitQueue.push(patient);
        }

        std::cout << "\n";
    }

    int time = 1;
    int completedPatients = 0;
    int totalPatients = patients.size();

    while (completedPatients < totalPatients) {
        std::cout << "\n==============================\n";
        std::cout << "[Time " << time << "]\n";
        std::cout << "==============================\n";

        if (time % 5 == 0) {
            renewAllPriorities(patients);
        }

        tryMovePatientsFromMemoryWaitQueue(
            memoryWaitQueue,
            scheduler,
            memoryManager
        );

        int resourceWaitSize = resourceWaitQueue.size();

        for (int i = 0; i < resourceWaitSize; i++) {
            Process* waitingPatient = resourceWaitQueue.front();
            resourceWaitQueue.pop();

            std::cout << "[RESOURCE WAIT CHECK] Retrying Patient "
                      << waitingPatient->id << "\n";

            if (resourceManager.requestResource(
                    waitingPatient,
                    waitingPatient->requestedResource
                )) {
                scheduler.addPatient(waitingPatient);
            } else {
                resourceWaitQueue.push(waitingPatient);
            }
        }

        if (scheduler.isEmpty()) {
            std::cout << "[CPU IDLE] No patient is ready this tick.\n";
            time++;
            continue;
        }

        Process* currentPatient = nullptr;

        if (schedulingMode == "FCFS") {
            currentPatient = scheduler.getNextPatientFCFS();
        } else {
            currentPatient = scheduler.getNextPatientRR();
        }

        if (currentPatient == nullptr || currentPatient->completed) {
            time++;
            continue;
        }

        std::cout << "[SELECTED] Patient " << currentPatient->id
                  << " (" << currentPatient->name << ")"
                  << " | Priority: "
                  << currentPatient->currentPriority << "\n";

        if (!currentPatient->hasResource()) {
            bool granted = resourceManager.requestResource(
                currentPatient,
                currentPatient->requestedResource
            );

            if (!granted) {
                resourceWaitQueue.push(currentPatient);
                time++;
                continue;
            }
        }

        std::cout << "[RUNNING] Patient " << currentPatient->id
                  << " completed tick "
                  << currentPatient->ticksCompleted + 1
                  << " of "
                  << currentPatient->totalTicksNeeded << "\n";

        currentPatient->runOneTick();

        std::cout << "[PRIORITY DECAY] Patient "
                  << currentPatient->id
                  << " priority changed from "
                  << currentPatient->currentPriority;

        currentPatient->decayPriority();

        std::cout << " to "
                  << currentPatient->currentPriority << "\n";

        if (currentPatient->isComplete()) {
            std::cout << "[TERMINATED] Patient "
                      << currentPatient->id
                      << " has finished treatment.\n";

            resourceManager.releaseResource(currentPatient);
            memoryManager.deallocate(currentPatient);
            completedPatients++;
        } else {
            if (schedulingMode == "RR") {
                std::cout << "[ROUND ROBIN] Patient "
                          << currentPatient->id
                          << " returned to ready queue.\n";
                scheduler.requeuePatient(currentPatient);
            } else {
                std::cout << "[FCFS] Patient "
                          << currentPatient->id
                          << " continues waiting in ready queue.\n";
                scheduler.requeuePatient(currentPatient);
            }
        }

        time++;
    }

    std::cout << "\n[SIMULATION COMPLETE]\n";

    for (Process* patient : patients) {
        delete patient;
    }

    return 0;
}
