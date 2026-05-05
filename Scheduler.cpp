#include "Scheduler.h"

void Scheduler::addPatient(Process* patient) {
    readyQueue.push(patient);
}

bool Scheduler::isEmpty() const {
    return readyQueue.empty();
}

Process* Scheduler::getNextPatientFCFS() {
    if (readyQueue.empty()) {
        return nullptr;
    }

    Process* patient = readyQueue.front();
    readyQueue.pop();
    return patient;
}

Process* Scheduler::getNextPatientRR() {
    if (readyQueue.empty()) {
        return nullptr;
    }

    Process* patient = readyQueue.front();
    readyQueue.pop();
    return patient;
}

void Scheduler::requeuePatient(Process* patient) {
    readyQueue.push(patient);
}
