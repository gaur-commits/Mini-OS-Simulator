## CRC Card: SimulationController

| **Class** | **Simulation** |
|---|---|
| **Responsibilities** | Maintain processes |
| | Add/remove/find processes |
| | Validate simulation requests |
| | Maintain/update simulation state |
| | Store selected scheduling algorithm |
| | Run simulation |
| | Generate/store simulation results |
| **Collaborators** | Process |
| | SchedulingAlgorithm |
| | SimulationResult |


---

## CRC Card: MemoryManager

| **Class** | **MemoryManager** |
|---|---|
| **Responsibilities** | Track total available system memory |
| | Allocate memory blocks to processes |
| | Deallocate memory when process finishes |
| | Validate process memory requirements |
| | Maintain free/allocated memory state |
| **Collaborators** | Process |
| | SimulationController |


---

## CRC Card: ReadyQueue

| **Class** | **ReadyQueue** |
|---|---|
| **Responsibilities** | Maintain the collection of ready processes |
| | Add/remove processes |
| | Find/check processes |
| | Provide the next process to be scheduled |
| | Maintain process ordering |
| **Collaborators** | Process |
| | SchedulingAlgorithm |


---

## CRC Card: Process

| **Class** | **Process** | |
|---|---|
| **Responsibilities** | Hold static identity data (Process ID, Required RAM, Total CPU Ticks) |
| | Track current execution status (Ready, Running, Terminated) |
| | Get and Update status (getState(), setState()) | 
| **Collaborators** | (None. It is a passive data entity) |


---

## CRC Card: Process

| **Class** | **Process** |
|---|---|
| **Responsibilities** | Hold static identity data (Process ID, Required RAM, Total CPU Ticks) |
| | Track current execution status (Ready, Running, Terminated) |
| | Get and update status (`getState()`, `setState()`) |
| **Collaborators** | None. It is a passive data entity |


---

## CRC Card — Scheduler

| Class  Scheduler |
| :--- | :--- |
| **Responsibilities** | **Collaborators** |
| • Check availability of ready processes before execution | • Process |
| • Execute scheduling algorithms (FCFS, SJF, Priority, Round Robin) | • SimulationController |
| • Pick next process based on arrival time, burst time, or priority | |
| • Calculate and generate metrics (Waiting Time, Turnaround Time) | |

