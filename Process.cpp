#include "Process.h"

Process::Process(int id, int run, int mem)
    : pid(id), state(NEW), runtime(run), memoryRequired(mem) {}
