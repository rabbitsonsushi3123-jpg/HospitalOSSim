#ifndef PROCESS_H
#define PROCESS_H

enum State { NEW, READY, RUNNING, WAITING, TERMINATED };

class Process {
public:
    int pid;
    State state;
    int runtime;
    int memoryRequired;

    Process(int id, int run, int mem);
};

#endif
