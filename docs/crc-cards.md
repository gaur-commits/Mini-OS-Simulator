# CRC Cards 

## CRC Card — SimulationController

| Class | SimulationController |
| :--- | :--- |
| **Responsibilities** | **Collaborators** |
| • Maintain processes | • Process |
| • Add/remove/find processes | • SchedulingAlgorithm |
| • Validate simulation requests | • SimulationResult |
| • Maintain/update simulation state | |
| • Store selected scheduling algorithm | |
| • Run simulation | |
| • Generate/store simulation results | |

---

## CRC Card — MemoryManager

| Class | MemoryManager |
| :--- | :--- |
| **Responsibilities** | **Collaborators** |
| • Track total available system memory | • Process |
| • Allocate memory blocks to processes | • SimulationController |
| • Deallocate memory when process finishes | |
| • Validate process memory requirements | |
| • Maintain free/allocated memory state | |

---

## CRC Card — ReadyQueue

| Class | ReadyQueue |
| :--- | :--- |
| **Responsibilities** | **Collaborators** |
| • Maintain the collection of ready processes | • Process |
| • Add/remove processes | • SchedulingAlgorithm |
| • Find/check processes | |
| • Provide the next process to be scheduled | |
| • Maintain process ordering | |

---

## CRC Card — Process

| Class | Process |
| :--- | :--- |
| **Responsibilities** | **Collaborators** |
| • Hold static identity data (Process ID, Required RAM, Total CPU Ticks) | • None (Passive data entity) |
| • Track current execution status (Ready, Running, Terminated) | |
| • Get and update status (`getState()`, `setState()`) | |

---

## CRC Card — Scheduler

| Class | Scheduler |
| :--- | :--- |
| **Responsibilities** | **Collaborators** |
| • Check availability of ready processes before execution | • Process |
| • Execute scheduling algorithms (FCFS, SJF, Priority, Round Robin) | • SimulationController |
| • Pick next process based on arrival time, burst time, or priority | |
| • Calculate and generate metrics (Waiting Time, Turnaround Time) | |
