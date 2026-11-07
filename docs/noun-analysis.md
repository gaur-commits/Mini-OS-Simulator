# Noun-Verb Analysis

---

## Use Case 1: Create Process

### Raw Candidate Nouns

user, system, process, process ID, CPU ticks, process state, process queue, process count, array, constructor, message, control panel.

### Raw Candidate Verbs

selects, enters, prompts, creates, initializes, stores, increments, displays, checks, allocates.

### Filtering

* **External actor:** `user` 
* **User actions:** `selects` and `enters` 
* **Attributes and values:** `process ID`, `CPU ticks`, `process state`, and `process count`
* **Interface terms:** `message`, `prompts`, and `displays`
* **Implementation details:** `process queue` and `array` were combined because the process queue is implemented as an array in `main()`.
* **Broad concepts:** `system` and `control panel`

### Surviving Class

```text
Process
```

### Relevant Attributes

```text
processId
cpuTicks
state
```

### Surviving Verbs and Responsibilities

```text
create process
initialize process
store process
count processes
```

---

## Use Case 2: Allocate Memory for a Process

### Raw Candidate Nouns

user, memory manager, memory, RAM, process, process ID, memory size, total memory, free memory, allocation message.

### Raw Candidate Verbs

selects, enters, requests, validates, checks, allocates, subtracts, displays, fails.

### Filtering

* **External actor:** `user`
* **User actions:** `selects`, `enters`, and `requests` 
* **Attributes and values:** `process ID`, `memory size`, `total memory`, and `free memory`
* **Synonyms:** `RAM` and `memory` were combined.
* **Output terms:** `allocation message`, `displays`, and `fails`
* **Merged verbs:** `checks` and `validates` were combined into `validates`.

### Surviving Class

```text
MemoryManager
```

### Relevant Attributes

```text
totalMemory
freeMemory
```

### Surviving Verbs and Responsibilities

```text
validate memory requirement
allocate memory
deallocate memory
```

---

## Use Case 3: Select and Run Scheduler

### Raw Candidate Nouns

user, scheduler, scheduling algorithm, FCFS, SJF, priority, Round Robin, process, process queue, active scheduler, algorithm choice, time quantum, process state, execution message.

### Raw Candidate Verbs

selects, enters, checks, chooses, assigns, prints, executes, changes, sets, displays, schedules.

### Filtering

* **External actor:** `user`
* **User actions:** `selects`, `enters`, and `chooses`
* **Attributes and values:** `algorithm choice`, `time quantum`, and `process state`
* **Output terms:** `execution message`, `prints`, and `displays`
* **Scheduler types:** `FCFS`, `SJF`, `Priority`, and `Round Robin`
* **Merged verbs:** `chooses` and `assigns`

### Surviving Classes

```text
Scheduler
Process
```

### Surviving Verbs and Responsibilities

```text
select scheduler
execute process
change process state
display scheduler type
```

---

## Use Case 4: View Total Processes

### Raw Candidate Nouns

user, process, process queue, process count, process ID, CPU ticks, process state, process information, total processes, output.

### Raw Candidate Verbs

selects, requests, counts, gets, iterates, retrieves, displays, prints.

### Filtering

* **External actor:** `user`
* **User actions:** `selects` and `requests`
* **Attributes:** `process count`, `process ID`, `CPU ticks`, `process state`, and `total processes`
* **Output terms:** `output`, `displays`, and `prints`
* **Merged nouns:** `process information` and `output` were combined as displayed process information.
* **Merged verbs:** `gets` and `retrieves` were combined into `gets`.

### Surviving Class

```text
Process
```

### Surviving Verbs and Responsibilities

```text
count processes
get process information
display process information
```

---

## Use Case 5: Shutdown System

### Raw Candidate Nouns

user, system, simulator, process, process object, dynamically allocated memory, cleanup message, application.

### Raw Candidate Verbs

selects, chooses, shuts down, exits, deletes, cleans up, releases, terminates, displays.

### Filtering

* **External actor:** `user`
* **User actions:** `selects` and `chooses`
* **Output terms:** `cleanup message` and `displays`
* **Broad concepts:** `system`, `simulator`, and `application`
* **Merged verbs:** `shuts down`, `exits`, and `terminates` were grouped as termination behavior.
* **Cleanup verbs:** `cleans up` and `releases` were grouped as deleting allocated process objects.

### Surviving Class

```text
Process
```

### Surviving Verbs and Responsibilities

```text
terminate system
delete process objects
release allocated objects
```

---

## Initial Surviving Class List from the Noun-Verb Analysis

The following are the core classes identified:

| Class | Reason for surviving the analysis |
|---|---|
| `Process` | Represents a process being created, executed, viewed, and deleted. |
| `MemoryManager` | Manages simulated memory allocation and deallocation. |
| `Scheduler` | Schedules the Algorithms. |

---

## Additional Classes Introduced During Implementation

While implementing `main.cpp`, additional classes were introduced to support inheritance, polymorphism, and the representation of different process and scheduler types.

These classes were not required to appear in the initial surviving class list because they are implementation-level specializations of the core concepts identified above.

| Implementation Class | Purpose in the Code |
|---|---|
| `PriorityProcess` | Specialized process type that adds a priority value. |
| `BackgroundProcess` | Specialized process type for background processing. |
| `SystemProcess` | Combines behavior from priority and background processes. |
| `FCFSScheduler` | Concrete scheduler derived from `Scheduler`. |
| `SJFScheduler` | Concrete scheduler derived from `Scheduler`. |
| `PriorityScheduler` | Concrete scheduler derived from `Scheduler`. |
| `RoundRobinScheduler` | Concrete scheduler derived from `Scheduler` and stores a time quantum. |

The `Scheduler::Info` nested class is also an implementation detail used by the scheduler hierarchy.
