# Mini OS Simulator — Use Case Specifications

> **Scope note:** This document describes the behavior implemented in the current C++ demonstration program. The program creates sample processes, manages simulated memory, selects a scheduler, and displays results. The scheduler classes do not implement the actual FCFS, SJF, Priority, or Round Robin algorithms.

## System Overview

The current program demonstrates the basic structure of a mini operating-system simulator through the following classes:

- `Process` — stores process information and state.
- `ReadyQueue` — stores processes waiting to be selected.
- `MemoryManager` — manages simulated RAM.
- `Scheduler` — abstract base class for scheduler types.
- `FCFSscheduler`, `SJFscheduler`, `PriorityScheduler`, and `RoundRobinScheduler` — concrete scheduler classes.
- `SimulationController` — coordinates the simulation.

The program creates a `SimulationController` with 1024 MB of simulated memory. It then creates sample processes, adds them to the controller and ready queue, allocates memory, selects an FCFS scheduler, runs the simulation, and displays the results.

The current version is not an interactive menu-based application. User input, process-file loading, and actual scheduling algorithms are not implemented.

---

## 1. Add Process to the Simulation

- **Use Case Name:** Add Process
- **Primary Actor:** `SimulationController`
- **Supporting Classes:** `Process`, `ReadyQueue`
- **Goal:** Store a process in the simulation and ready queue.
- **Preconditions:** The simulation controller has been created and the ready queue is not full.
- **Postconditions:** The process is stored in the controller's process list and added to the ready queue.
- **Trigger:** `SimulationController::addProcess()` is called.

### Main Flow

1. The program creates a `Process` object with an ID, required RAM, and CPU tick count.
2. The process is added to the controller's process list.
3. The same process is added to the `ReadyQueue`.
4. The process initially has the state `New`.

### Alternate Flow: Ready Queue Is Full

1. `ReadyQueue::addProcess()` checks the queue size.
2. If the queue already contains 10 processes, it throws a `QueueFullException`.
3. The exception is caught by the calling code.
4. The process is not added to the queue.

### Relevant Methods

- `SimulationController::addProcess()`
- `ReadyQueue::addProcess()`
- `Process::Process()`

---

## 2. Allocate Memory for a Process

- **Use Case Name:** Allocate Memory
- **Primary Actor:** `MemoryManager`
- **Supporting Class:** `Process`
- **Goal:** Allocate the RAM required by a process.
- **Preconditions:** A `MemoryManager` and a `Process` object exist.
- **Postconditions:** The required RAM is subtracted from free memory when enough memory is available.
- **Trigger:** `MemoryManager::allocateMemory()` is called.

### Main Flow

1. The memory manager receives a process object.
2. It reads the process's required RAM using `Process::getRequiredRAM()`.
3. `validateMemoryRequirement()` checks whether enough free memory is available.
4. The required amount is subtracted from `freeMemory`.
5. The amount is added to `allocatedMemory`.

### Alternate Flow: Insufficient Memory

1. The requested RAM is greater than the available free memory.
2. `MemoryManager::allocateMemory()` throws an `OutOfMemoryException`.
3. The derived exception is caught before the base `OSException`.
4. The free-memory value remains unchanged.

### Deallocate Memory

When a process finishes, `MemoryManager::deallocateMemory()` adds its required RAM back to free memory. The current demonstration calls this method for the first two sample processes.

### Relevant Methods

- `MemoryManager::validateMemoryRequirement()`
- `MemoryManager::allocateMemory()`
- `MemoryManager::deallocateMemory()`
- `MemoryManager::getFreeMemory()`

---

## 3. Select and Run a Scheduler

- **Use Case Name:** Select and Run Scheduler
- **Primary Actor:** `SimulationController`
- **Supporting Classes:** `Scheduler`, `ReadyQueue`, and a concrete scheduler class
- **Goal:** Select a process through the scheduler interface.
- **Preconditions:** A scheduler pointer has been assigned and the ready queue contains at least one process.
- **Postconditions:** A process is selected and displayed with the temporary state `Running`.
- **Trigger:** `SimulationController::runSimulation()` is called.

### Main Flow

1. The controller changes the simulation state to `Running`.
2. The controller checks whether a scheduler exists.
3. The scheduler checks whether the ready queue contains a process.
4. The scheduler's `pickNextProcess()` method is called through a base-class pointer.
5. The selected process is given the temporary state `Running`.
6. The selected process is displayed.

### Alternate Flow: No Scheduler or Process Available

1. The controller finds that no scheduler has been assigned or the ready queue is empty.
2. The controller displays a message that no scheduler or process is available.
3. No process is selected.

### Scheduler Demonstration Behavior

All four concrete scheduler classes currently return the first process in the ready queue:

- `FCFSscheduler` — placeholder for FCFS selection.
- `SJFscheduler` — placeholder for SJF selection.
- `PriorityScheduler` — placeholder for priority-based selection.
- `RoundRobinScheduler` — placeholder for Round Robin selection and stores a time quantum.

The classes do not compare CPU ticks, compare priorities, rotate processes, or calculate scheduling results.

### Relevant Methods

- `Scheduler::checkAvailability()`
- `Scheduler::pickNextProcess()`
- `FCFSscheduler::pickNextProcess()`
- `SJFscheduler::pickNextProcess()`
- `PriorityScheduler::pickNextProcess()`
- `RoundRobinScheduler::pickNextProcess()`
- `SimulationController::runSimulation()`

---

## 4. Generate Simulation Results

- **Use Case Name:** Generate Results
- **Primary Actor:** `SimulationController`
- **Supporting Classes:** `Process`, `MemoryManager`
- **Goal:** Display the current simulation state, free memory, and process information.
- **Preconditions:** The controller has been created.
- **Postconditions:** Simulation information is printed to the console.
- **Trigger:** `SimulationController::generateResults()` is called.

### Main Flow

1. The controller displays the simulation state.
2. The controller displays the amount of free memory.
3. The controller iterates through its stored process list.
4. Each process displays its detailed information.
5. The overloaded `displayInfo(bool)` method is used for detailed output.

### Relevant Methods

- `SimulationController::generateResults()`
- `Process::displayInfo()`
- `Process::displayInfo(bool)`
- `operator<<`

**Implementation note:** The scheduler receives and returns a `Process` object by value. Therefore, changing the selected process to `Running` changes the displayed copy, not the original process stored in the controller's list.

---

## 5. Handle Simulation Errors

- **Use Case Name:** Handle Simulation Errors
- **Primary Actor:** `SimulationController`
- **Supporting Classes:** `OSException`, `OutOfMemoryException`, `QueueFullException`
- **Goal:** Report memory and ready-queue errors without terminating unexpectedly.
- **Trigger:** An invalid resource request is made.

### Main Flow

1. The program enters a `try` block.
2. A memory or queue operation detects an error.
3. The operation throws a user-defined exception.
4. A specific derived exception is caught first.
5. A general `OSException` catch block handles other operating-system errors.
6. The error message is displayed using `what()`.

### Supported Exceptions

- `OutOfMemoryException` — insufficient simulated RAM.
- `QueueFullException` — the ready queue has reached its maximum size.
- `OSException` — common base class for simulator exceptions.

---

## Demonstration Features

The current code also demonstrates the following C++ concepts:

- Inheritance through the scheduler hierarchy.
- Virtual and pure virtual functions.
- Access specifiers.
- Constructor and method overloading.
- Static process counter and static accessor function.
- Nested `Scheduler::Info` class.
- Friend stream operator overloading using `operator<<`.
- Pointers to base and derived objects.
- Object slicing using `PriorityProcess` copied into a `Process` object.
- User-defined exception classes.

These demonstrations support the project requirements but do not represent additional simulator use cases.

---

## Functionality Not Implemented in the Current Version

The following features are not implemented and should not be described as current functionality:

- Interactive menu-based process creation.
- Loading process information from a file.
- Actual FCFS scheduling logic.
- Actual SJF scheduling logic.
- Actual Priority scheduling logic.
- Actual Round Robin scheduling logic.
- Scheduling based on arrival time, CPU burst time, or priority.
- Process rotation using a time quantum.
- Waiting-time, turnaround-time, completion-time, or average-statistic calculations.
- Real process execution or context switching.
- Multithreading and thread synchronization.
- Virtual base classes.
- Java-style `throws` declarations and `finally` blocks.
- Automatic process termination management.
- Allocation records linked to individual process IDs.
