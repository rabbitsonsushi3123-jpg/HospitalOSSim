
# HospitalOSSim

HospitalOSSim is a C++ operating system simulation project that models how a hospital manages patients, memory, scheduling, and limited medical resources.

The simulation applies core operating system concepts to a hospital environment where patients act like processes and hospital equipment acts like shared hardware resources.

==================================================
PROJECT PURPOSE
==================================================

This project demonstrates several important operating system concepts including:

- Process scheduling
- Memory management
- Resource allocation
- Waiting queues
- Dynamic priorities and aging
- CPU execution simulation
- Round Robin scheduling
- First Come First Serve scheduling
- Starvation prevention techniques

The goal of the project is to show how an operating system handles multiple processes competing for limited resources while maintaining fairness and efficiency.

==================================================
SYSTEM CONFIGURATION
==================================================

The operating system simulator uses:

- 1024 units of total system memory
- Dynamic memory allocation
- Shared hospital resources
- Ready queues and waiting queues
- Tick-based CPU execution

The 1024-unit memory pool is managed by the MemoryManager and shared among all active patient processes.

==================================================
MAIN FEATURES
==================================================

1. Scheduling Algorithms
-------------------------

The simulation supports two scheduling modes:

FCFS (First Come First Serve)
- Patients are treated in the order they arrive.

RR (Round Robin)
- Patients take turns executing one tick at a time.

The user selects the scheduling algorithm at runtime.

==================================================

2. Memory Management
---------------------

The MemoryManager controls memory allocation using a total memory size of 1024 units.

If enough memory is available:
- The patient is added to the ready queue.

If memory is unavailable:
- The patient is placed into a memory wait queue.

Memory is released after the patient completes treatment.

The simulator continuously checks the memory wait queue to see if waiting patients can now be allocated memory.

==================================================

3. Resource Management
-----------------------

Patients may require special hospital equipment before they can run.

Resources include:
- MRI Scanner
- Blood Lab
- Operating Room
- X-Ray Machine

If a resource is busy:
- The patient waits in the resource wait queue.

The simulator repeatedly retries blocked resource requests until the resource becomes available.

Resources are released after use.

==================================================

4. Dynamic Priorities and Aging
--------------------------------

Each patient has:
- Base priority
- Current priority

While a patient executes:
- Its priority gradually decays.

To prevent starvation, the scheduler implements an aging system.

Every 5 simulation ticks:
- All unfinished patients have their priorities refreshed back to their original base priority.

This ensures that lower-priority patients are eventually able to execute and are not permanently blocked by higher-priority patients.

This aging mechanism improves fairness in the scheduler and prevents starvation within the system.

==================================================
PROJECT FILES
==================================================

main.cpp
---------
The main simulation driver.

Responsibilities:
- Creates patients
- Starts the simulation
- Handles scheduling
- Processes wait queues
- Runs time ticks
- Tracks completed patients
- Applies aging every 5 ticks
- Controls CPU execution flow

==================================================

Process.h / Process.cpp
------------------------

Represents a patient process.

Each process stores:
- ID
- Name
- Memory requirement
- Priority
- Tick count
- Requested resource
- Completion state

Main methods:
- runOneTick()
- decayPriority()
- renewPriority()
- assignResource()
- releaseResource()

==================================================

Scheduler.h / Scheduler.cpp
----------------------------

Handles the ready queue.

Functions:
- Add patients
- Select next patient
- Requeue unfinished patients
- Support FCFS and RR scheduling

Uses:
std::queue<Process*>

The scheduler works together with the aging system to help prevent starvation.

==================================================

MemoryManager.h / MemoryManager.cpp
-----------------------------------

Controls memory allocation and deallocation.

Features:
- Tracks available memory
- Uses a 1024-unit memory pool
- Grants memory
- Denies memory requests
- Releases memory after completion

==================================================

MemoryModel.h / MemoryModel.cpp
--------------------------------

Implements a lower-level memory block system.

Features:
- Splits memory into blocks
- Tracks free blocks
- Allocates blocks
- Frees blocks

This simulates basic memory partitioning and memory fragmentation behavior.

==================================================

ResourcePool.h / ResourcePool.cpp
----------------------------------

Stores all available hospital resources.

Tracks:
- Resource names
- Resource availability

==================================================

ResourceManager.h / ResourceManager.cpp
----------------------------------------

Handles resource requests.

Functions:
- Grant resources
- Deny busy resources
- Release resources

==================================================

Logger.h / Logger.cpp
----------------------

Simple logging utility used for console messages and debugging.

==================================================
SIMULATION FLOW
==================================================

Step 1:
The user selects FCFS or RR scheduling.

Step 2:
Patients are created with:
- Memory requirements
- Priorities
- Tick durations
- Resource requests

Step 3:
Patients request memory.

If memory is available:
- They enter the ready queue.

Otherwise:
- They enter the memory wait queue.

Step 4:
The scheduler selects a patient.

Step 5:
The patient requests its required resource.

If the resource is unavailable:
- The patient waits in the resource wait queue.

Step 6:
The patient executes one CPU tick.

During execution:
- Tick count increases
- Priority decays
- Completion is checked

Step 7:
Every 5 ticks:
- The aging system refreshes all unfinished patient priorities.

This prevents starvation and improves fairness.

Step 8:
When finished:
- Resources are released
- Memory is freed
- The patient terminates

==================================================
EXAMPLE PATIENT
==================================================

Example:

new Process(1, "Patient A", 300, 5, 3, 0)

Meaning:
- ID = 1
- Name = Patient A
- Memory required = 300
- Priority = 5
- Needs 3 ticks
- Requests MRI Scanner

==================================================
EXAMPLE OUTPUT
==================================================

[SIMULATION STARTED]

[NEW PATIENT] Patient 1

[MEMORY REQUEST] Patient 1 needs 300 units

[MEMORY GRANTED]

[RESOURCE REQUEST] Patient 1 requests MRI Scanner

[RESOURCE GRANTED]

[RUNNING] Patient 1 completed tick 1 of 3

[PRIORITY DECAY] Patient 1 priority changed

[PRIORITY RENEWAL] 5 ticks passed. Renewing all patient priorities.

==================================================
DATA STRUCTURES USED
==================================================

Queues
------
Used for:
- Ready queue
- Memory wait queue
- Resource wait queue

Vectors
-------
Used for:
- Patient storage
- Memory blocks
- Resource lists

==================================================
HOW TO COMPILE
==================================================

g++ main.cpp Process.cpp Scheduler.cpp MemoryManager.cpp MemoryModel.cpp ResourceManager.cpp ResourcePool.cpp Logger.cpp -o HospitalOSSim

==================================================
HOW TO RUN
==================================================

Linux/Mac:
./HospitalOSSim

Windows:
HospitalOSSim.exe

==================================================
POSSIBLE FUTURE IMPROVEMENTS
==================================================

Possible extensions:
- Priority queue scheduling
- Multi-level feedback queues
- Deadlock detection
- GUI support
- Virtual memory
- Multi-threading
- Statistics dashboard
- Better memory visualization

==================================================
EDUCATIONAL PURPOSE
==================================================

This project was created to demonstrate operating system concepts in a practical and understandable simulation environment using C++.

The simulator combines:
- CPU scheduling
- Memory management
- Resource allocation
- Aging and starvation prevention
- Queue management

Useful for:
- Operating Systems classes
- Scheduling demonstrations
- Memory management demonstrations
- Simulation projects

==================================================
NOTES
==================================================

The README documentation is based directly on the uploaded source code including:
- The simulation loop in main.cpp
- Scheduler implementation
- Memory allocation system
- Resource management system
- Aging and priority renewal system
- Process lifecycle implementation
- Queue handling logic
- Memory block modeling

==================================================
AUTHORS OF PROGRAM
==================================================
Dianna Paolina Dominguez 
Karnvir Singh
Shruti Fnu
Matthew Alan James Kramer-Robertson
