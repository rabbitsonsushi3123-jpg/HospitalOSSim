#pragma once
#include <queue>
#include <vector>
#include <string>
#include "Process.h"

class Scheduler {
private:
    std::queue<Process*> readyQueue;

public:
    void addPatient(Process* patient);
    bool isEmpty() const;

    Process* getNextPatientFCFS();
    Process* getNextPatientRR();

    void requeuePatient(Process* patient);
};
