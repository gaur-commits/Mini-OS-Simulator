# Mini OS Simulator — Use Case Specifications

## 1. Create Process

- **Use Case Name:** Create Process
- **Primary Actor:** User
- **Stakeholders:**
  - User — wants to create and store a new process.
  - Simulator — stores the process information for later use.
- **Preconditions:**
  - The simulator is running.
  - The process queue has space for another process.
- **Postconditions:**
  - A new process is created.
  - The process is stored in the process queue.
  - The process is assigned the initial state `Ready`.
  - The total process count increases by one.
- **Trigger:** The user selects **Create New Process** from the control panel.

### Main Flow

1. The user selects **Create New Process**.
2. The simulator prompts the user to enter a process ID.
3. The user enters the process ID.
4. The simulator prompts the user to enter the required CPU ticks.
5. The user enters the CPU tick requirement.
6. The simulator creates a new `Process` object using the entered values.
7. The simulator stores the new process in the process queue.
8. The simulator assigns the process the state `Ready`.
9. The simulator displays a success message.

### Alternate Flow 1: Process Queue Is Full

1a. The user selects **Create New Process**.
2a. The simulator finds that the process queue already contains 10 processes.
3a. The simulator displays a message stating that the process queue is full.
4a. No new process is created.
5a. The simulator returns to the control panel.

### Alternate Flow 2: Invalid Process Input

3a. The user enters an invalid process ID or CPU tick value.
4a. The simulator displays an invalid-input message.
5a. The simulator does not create the process.
6a. The simulator returns to the control panel.

---

## 2. Allocate Memory for a Process

- **Use Case Name:** Allocate Memory for a Process
- **Primary Actor:** User
- **Stakeholders:**
  - User — wants to allocate a specified amount of simulated memory.
  - Memory Manager — updates the amount of available simulated memory.
  - Process — requires memory for its execution.
- **Preconditions:**
  - The simulator is running.
  - The memory manager has available simulated memory.
- **Postconditions:**
  - The requested memory is allocated when sufficient memory is available.
  - The free-memory value is updated after successful allocation.
  - The free-memory value remains unchanged when allocation fails.
- **Trigger:** The user selects **Allocate Memory for a Process** from the control panel.

### Main Flow

1. The user selects **Allocate Memory for a Process**.
2. The simulator prompts the user to enter a process ID.
3. The user enters the process ID.
4. The simulator prompts the user to enter the required memory size in MB.
5. The user enters the requested memory size.
6. The memory manager checks whether sufficient free memory is available.
7. The memory manager subtracts the requested amount from the free-memory value.
8. The simulator displays a successful allocation message.
9. The simulator displays the updated free-memory value.

### Alternate Flow 1: Insufficient Free Memory

6a. The requested memory size is greater than the available free memory.
7a. The memory manager rejects the allocation request.
8a. The simulator displays an allocation-failed message.
9a. The free-memory value remains unchanged.

### Alternate Flow 2: Invalid Memory Size

5a. The user enters a zero, negative, or otherwise invalid memory size.
6a. The simulator displays an invalid-memory-size message.
7a. The memory manager does not change the free-memory value.
8a. The simulator returns to the control panel.

---

## 3. Select and Run Scheduler

- **Use Case Name:** Select and Run Scheduler
- **Primary Actor:** User
- **Stakeholders:**
  - User — wants to select a scheduler and run it for a process.
  - Simulator — invokes the selected scheduler and updates the process state.
  - Process — is selected for execution by the scheduler.
- **Preconditions:**
  - The simulator is running.
  - At least one process has been created.
  - Scheduler options are available.
- **Postconditions:**
  - The selected scheduler is set as the active scheduler.
  - The selected scheduler type is displayed.
  - The scheduler is invoked for the selected process.
  - The process state changes to `Running`.
- **Trigger:** The user selects **Select & Run Scheduler** from the control panel.

### Main Flow

1. The user selects **Select & Run Scheduler**.
2. The simulator checks whether at least one process exists.
3. The simulator displays the available scheduler options.
4. The user selects a scheduler type.
5. The simulator sets the selected scheduler as the active scheduler.
6. The simulator displays the selected scheduler type.
7. The simulator selects the most recently created process.
8. The active scheduler executes the selected process.
9. The process state is changed to `Running`.

### Alternate Flow 1: No Processes Available

2a. The simulator finds that no processes have been created.
3a. The simulator displays a message asking the user to create a process first.
4a. The scheduler is not invoked.
5a. The simulator returns to the control panel.

### Alternate Flow 2: Invalid Scheduler Selection

4a. The user enters a number that does not correspond to an available scheduler.
5a. The simulator displays an invalid-scheduler-choice message.
6a. No scheduler is selected or invoked.
7a. The simulator returns to the control panel.

---

## 4. View Total Processes

- **Use Case Name:** View Total Processes
- **Primary Actor:** User
- **Stakeholders:**
  - User — wants to view the number and details of created processes.
  - Simulator — retrieves and displays the stored process information.
- **Preconditions:**
  - The simulator is running.
- **Postconditions:**
  - The total number of processes is displayed.
  - The information of each available process is displayed.
  - No process information is changed.
- **Trigger:** The user selects **View Total Processes** from the control panel.

### Main Flow

1. The user selects **View Total Processes**.
2. The simulator retrieves the total process count.
3. The simulator displays the total number of processes.
4. The simulator iterates through the process queue.
5. The simulator displays the process ID, CPU ticks, and state of each process.
6. The simulator returns to the control panel.

### Alternate Flow 1: No Processes Have Been Created

2a. The simulator finds that the total process count is zero.
3a. The simulator displays a message stating that no processes are available.
4a. The simulator does not display process details.
5a. The simulator returns to the control panel.

### Alternate Flow 2: Empty Queue Entries Are Found

4a. The simulator finds an empty entry while iterating through the process queue.
5a. The simulator skips the empty entry.
6a. The simulator continues displaying information for the remaining processes.
7a. The simulator returns to the control panel after completing the iteration.

---

## 5. Shutdown System

- **Use Case Name:** Shutdown System
- **Primary Actor:** User
- **Stakeholders:**
  - User — wants to close the simulator.
  - Simulator — must stop execution and release allocated process objects.
  - Operating system — receives control after the simulator terminates.
- **Preconditions:**
  - The simulator is running.
  - The control panel is being displayed.
- **Postconditions:**
  - The simulator control loop ends.
  - Dynamically allocated process objects are deleted.
  - The simulator terminates.
- **Trigger:** The user selects **Shutdown System** from the control panel.

### Main Flow

1. The user selects **Shutdown System**.
2. The simulator exits the control loop.
3. The simulator displays a shutdown message.
4. The simulator deletes the dynamically allocated process objects.
5. The simulator terminates.

### Alternate Flow 1: No Processes Exist

1a. The user selects **Shutdown System** when no processes have been created.
2a. The simulator exits the control loop.
3a. The simulator finds no process objects to delete.
4a. The simulator displays a shutdown message.
5a. The simulator terminates.

### Alternate Flow 2: Empty Queue Entries Exist

4a. The simulator finds an empty entry while deleting process objects.
5a. The simulator skips the empty entry instead of deleting it.
6a. The simulator continues deleting all remaining process objects.
7a. The simulator terminates after cleanup is complete.
