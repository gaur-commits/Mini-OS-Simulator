# Mini OS Simulator — Use Case Specifications

> **Scope note:** This document describes the functionality implemented in the current command-line C++ version of the Mini OS Simulator. The scheduler classes display messages and change a process state to `Running`; they do **not** implement the actual FCFS, SJF, Priority, or Round Robin scheduling algorithms.

## System Overview

The user interacts with the simulator through a terminal-based control panel. The current version supports:

- Creating up to 10 processes by entering a process ID and CPU tick requirement.
- Manually requesting simulated memory allocation by entering a process ID and memory size.
- Selecting one of four scheduler types and invoking its `executeProcess()` method on the most recently created process.
- Viewing the total number of processes created and their basic information.
- Shutting down the simulator.

The simulator starts with 1024 MB of simulated RAM. This value is fixed in `main()` and is not configurable through the menu.

**Important implementation detail:** The memory manager only updates the free-memory counter. It does not maintain an allocation record for each process or verify that a process ID exists. The scheduler classes do not reorder processes, compare their CPU burst times, manage a ready queue, or calculate scheduling statistics.

---

## 1. Create Process

- **Use Case Name:** Create Process
- **Primary Actor:** User
- **Stakeholders:**
  - User — wants to add a process to the simulator.
  - Simulator — stores the process information for later display and scheduler demonstration.
- **Preconditions:**
  - The simulator has been started.
  - Fewer than 10 processes have been created.
- **Postconditions:**
  - A new `Process` object is created and stored in the process queue.
  - The process is initially assigned the state `Ready`.
  - The total process count increases by one.
- **Trigger:** The user selects **Create New Process** from the control panel.

### Main Flow

1. The simulator displays the control panel.
2. The user selects **Create New Process**.
3. The simulator prompts for a process ID.
4. The user enters the process ID.
5. The simulator prompts for the required CPU ticks.
6. The user enters the CPU tick requirement.
7. The simulator creates a `Process` object with the entered values.
8. The simulator stores the new process in its process queue.
9. The simulator displays a success message.

### Alternate Flow 1: Process Queue Is Full

2a. The user selects **Create New Process**, but 10 processes have already been created.  
3a. The simulator displays a message that the queue is full.  
4a. No new process is created, and the simulator returns to the control panel.

---

## 2. Allocate Memory for a Process

- **Use Case Name:** Allocate Memory for a Process
- **Primary Actor:** User
- **Stakeholders:**
  - User — wants to allocate a specified amount of simulated RAM.
  - Memory Manager — updates the amount of free simulated RAM.
- **Preconditions:**
  - The simulator is running.
- **Postconditions:**
  - If enough free memory is available, the requested amount is subtracted from the free-memory counter.
  - If insufficient memory is available, the free-memory counter remains unchanged.
- **Trigger:** The user selects **Allocate Memory for a Process** from the control panel.

### Main Flow

1. The user selects **Allocate Memory for a Process**.
2. The simulator prompts for a process ID.
3. The user enters a process ID.
4. The simulator prompts for a memory size in MB.
5. The user enters the requested memory size.
6. The `MemoryManager` checks whether the requested size is no greater than the available free memory.
7. If sufficient memory is available, the manager subtracts the requested size from free memory.
8. The simulator displays the allocation message and updated free-memory amount.

### Alternate Flow 1: Insufficient Free Memory

6a. The requested memory size is greater than the available free memory.  
7a. The simulator displays an allocation-failed message.  
8a. The free-memory amount remains unchanged.

**Note:** The current implementation does not verify that the entered process ID belongs to a process in the simulator. It also does not store individual allocation records or prevent repeated allocations for the same ID.

---

## 3. Select and Run Scheduler

- **Use Case Name:** Select and Run Scheduler
- **Primary Actor:** User
- **Stakeholders:**
  - User — wants to select a scheduler type and see it invoked for a process.
  - Simulator — demonstrates the scheduler class interface and process-state update.
- **Preconditions:**
  - The simulator is running.
  - At least one process has been created.
- **Postconditions:**
  - The selected scheduler's type is displayed.
  - The scheduler's `executeProcess()` method is called for the most recently created process.
  - That process's state is changed to `Running`.
- **Trigger:** The user selects **Select & Run Scheduler** from the control panel.

### Main Flow

1. The user selects **Select & Run Scheduler**.
2. The simulator checks whether at least one process has been created.
3. The simulator displays the available scheduler choices:
   - FCFS
   - SJF
   - Priority
   - Round Robin
4. The user selects one of the available scheduler types.
5. The simulator sets the selected scheduler as the active scheduler.
6. The simulator displays the selected scheduler's type.
7. The simulator selects the most recently created process.
8. The selected scheduler displays its execution message and changes that process's state to `Running`.

### Alternate Flow 1: No Processes Available

2a. The simulator finds that no processes have been created.  
3a. The simulator displays a message asking the user to create a process first.  
4a. The scheduler is not invoked, and the simulator returns to the control panel.

### Alternate Flow 2: Invalid Scheduler Selection

4b. The user enters a number outside the available choices.  
5b. The simulator displays an invalid scheduler choice message.  
6b. No scheduler is invoked, and the simulator returns to the control panel.

### Scheduler Demonstration Behaviour

The four scheduler classes currently provide demonstration messages:

- **FCFS:** Displays an FCFS execution message.
- **SJF:** Displays an SJF execution message.
- **Priority:** Displays a priority-based execution message.
- **Round Robin:** Displays an execution message that includes its configured time quantum (20 ticks in the current `main()` function).

These classes do **not** implement the corresponding scheduling algorithms. In particular, the current version does not order processes by arrival time, burst time, or priority; does not rotate processes through a ready queue; and does not calculate waiting time, turnaround time, or completion time. Only the most recently created process is passed to `executeProcess()`.

---

## 4. View Total Processes

- **Use Case Name:** View Total Processes
- **Primary Actor:** User
- **Stakeholders:**
  - User — wants to see how many processes have been created and inspect their basic information.
  - Simulator — displays the stored process information.
- **Preconditions:**
  - The simulator is running.
- **Postconditions:**
  - The total number of created processes is displayed.
  - Basic information for each created process is displayed.
  - No process information is modified.
- **Trigger:** The user selects **View Total Processes** from the control panel.

### Main Flow

1. The user selects **View Total Processes**.
2. The simulator displays the total number of processes created.
3. The simulator iterates through the process queue.
4. For each process, the simulator displays its process ID, CPU ticks, and current state.
5. The simulator returns to the control panel.

### Alternate Flow: No Processes Have Been Created

If no processes have been created, the simulator displays a total count of zero and does not display any process entries.

---

## 5. Shutdown System

- **Use Case Name:** Shutdown System
- **Primary Actor:** User
- **Stakeholders:**
  - User — wants to close the simulator.
  - Simulator — needs to release dynamically allocated process objects before terminating.
- **Preconditions:**
  - The simulator is running.
- **Postconditions:**
  - The control loop ends.
  - Dynamically allocated process objects are deleted.
  - The application terminates.
- **Trigger:** The user selects **Shutdown System** from the control panel.

### Main Flow

1. The user selects **Shutdown System**.
2. The simulator exits the control loop.
3. The simulator displays a shutdown message.
4. The simulator deletes the dynamically allocated process objects.
5. The application terminates.

---

## Functionality Not Implemented in the Current Version

The following features may be considered for future development, but they should not be presented as implemented functionality:

- Loading process information from an input file.
- Modifying or removing an existing process through the menu.
- Actual FCFS, SJF, Priority, or Round Robin scheduling logic.
- Scheduling all processes according to arrival time, burst time, or priority.
- A ready queue, time-based process rotation, or real context switching.
- Waiting-time, turnaround-time, completion-time, or average scheduling-statistic calculations.
- Pausing and resuming a simulation.
- Configuring total RAM through the menu.
- Tracking memory allocations against individual process IDs or validating process IDs during allocation.
- Automatically allocating or releasing memory when processes are created, executed, or terminated.
