# Noun-Verb Analysis

## Use Case 1: Create Process - Noun/Verb Analysis

### 1. Raw Candidate List (Extracted Nouns):
user, system, program, input file, machine, process, memory, controller, tracking list, terminal, command, file name, line, integers, id, memory requirement, cpu ticks, message, directory, file error, warning, setup.

 ### 2. Discarded Candidates & Filters Applied
    
   * Filter 1 (Actors/External Entities): user, system, program, machine, terminal. (These are physical hardware, human users, or the overall application boundary).

   * Filter 2 (Attributes/Values): file name, line, integers, id, memory requirement, cpu ticks, directory, message, command. (These are just basic string or integer variables, not blueprints for a class).

   * Filter 3 (Redundant/Synonyms): input file, setup. (Input file is just standard Java/Python File I/O, setup is a generic word for the whole process).

   * Filter 4 (Actions/Events/UI): file error, warning. (These are exceptions and console printouts, not architectural classes).

### 3. Surviving Classes (The Core Architecture):

  * SimulationController (Derived from "controller" - the boss managing the file loading)

  * Process (The actual data entity being created)

  * MemoryManager (Derived from "memory" - where the process will eventually live)

  * ReadyQueue (Derived from "tracking list" - where the processes are stored after creation)

### 4. Verb Analysis (Identifying Methods):

  * read, parse, load -> Becomes loadProcesses(fileName) in SimulationController.

  * create, instantiate -> Becomes the constructor Process(id, memory, ticks).

  * add to tracking list -> Becomes enqueue(process) in ReadyQueue.
---

## Use Case 2: Run Simulation - Noun/Vern Analysis

## 1. Raw Candidate List (Extracted Nouns)

user, simulation user, system, simulation, process, scheduling algorithm, simulation result, command, terminal, option, message, main menu, step, main flow, alternate flow.

## 2. Discarded Candidates and Filters Applied

- **Filter 1 — Actors/External Entities:** `user`, `simulation user`, `system`.  
  They interact with or represent the complete application, so they are not core domain classes.

- **Filter 2 — Attributes/Values:** `command`, `option`.  
  They are simple input values, not independent objects requiring classes.

- **Filter 3 — Redundant/Synonyms:** `simulation user`, `simulation`.  
  `Simulation User` means the same as `User`. The simulation operation is managed by `SimulationController`, so a separate `Simulation` class is unnecessary here.

- **Filter 4 — Actions/Events/UI:** `terminal`, `message`, `main menu`, `step`, `main flow`, `alternate flow`.  
  These describe the interface, displayed output, or use-case sequence rather than architectural classes.

## 3. Surviving Classes (Core Architecture)

- **SimulationController** — validates the required data, runs the simulation, and coordinates the result.
- **Process** — represents each process used in the simulation.
- **SchedulingAlgorithm** — represents the selected algorithm, such as FCFS, SJF, Priority, or Round Robin.
- **SimulationResult** — stores the generated output, such as waiting time, turnaround time, and execution order.

## 4. Verb Analysis (Possible Operations)

| Extracted verb/action | Possible method | What happens? |
|---|---|---|
| selects algorithm | `selectAlgorithm()` | Stores the scheduling algorithm chosen by the user. |
| checks processes | `validateProcesses()` | Confirms that at least one valid process exists. |
| checks algorithm | `validateAlgorithm()` | Confirms that an algorithm has been selected. |
| runs simulation | `runSimulation()` | Executes the processes using the selected algorithm. |
| generates results | `generateResult()` | Creates the simulation output. |
| displays results | `displayResult()` | Shows the result to the user. |
| returns to menu | `returnToMainMenu()` | Goes back when the simulation cannot run. |
| resumes simulation | `resumeSimulation()` | Continues after the user selects an algorithm. |

