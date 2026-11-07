# CRC Cards

## CRC Card — Process

| Class | Process |
| :--- | :--- |
| **Responsibilities** | **Collaborators** |
| • Hold process identity data such as Process ID and required CPU ticks | • MemoryManager |
| • Track the current execution state of the process | • Scheduler |
| • Initialize a newly created process in the `Ready` state | |
| • Get and update the process state | |
| • Provide process information for display | |
| • Maintain or provide the total process count | |

---

## CRC Card — MemoryManager

| Class | MemoryManager |
| :--- | :--- |
| **Responsibilities** | **Collaborators** |
| • Track total available simulated memory | • Process |
| • Track the amount of free memory | |
| • Validate process memory requirements | |
| • Allocate memory for processes | |
| • Deallocate memory when it is released | |
| • Update the free-memory state after allocation or deallocation | |

---

## CRC Card — Scheduler

| Class | Scheduler |
| :--- | :--- |
| **Responsibilities** | **Collaborators** |
| • Represent the general scheduling responsibility | • Process |
| • Provide a common interface for scheduler types | |
| • Select and identify the active scheduler | |
| • Display the selected scheduler type | |
| • Execute a selected process | |
| • Request a change in the process state | |
| • Support scheduling strategies such as FCFS, SJF, Priority, and Round Robin | |
