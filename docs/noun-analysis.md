# Noun-Verb Analysis

## Use Case 1: Create Process - Combined Noun & Verb Analysis

### 1. Raw Candidate List

   **Candidate Nouns:** user, system, program, input file, machine, process, memory, controller, tracking list, terminal, command, file name, line, integers, id, memory requirement, cpu ticks, message, directory, file error, warning, setup.

   **Candidate Verbs:** starts, running, exists, created, added, selects, load, prompts, enter, inputs, opens, reads, parses, closes, displays, loops, catches, encounters, ignores, continues, finishes.

### 2. Noun and Verb filtering

   * **Filter 1: Outside the system? (actor not class)**

     * Discarded Nouns: user, machine, terminal. (Reason: These are humans or physical hardware outside our software code).

     * Discarded Verbs: selects, enter, inputs. (Reason: These are actions performed physically by the human user, not functions the system executes).

   * **Filter 2: A property of something else? (attribute not class)**

     * Discarded Nouns: file name, line, integers, id, memory requirement, cpu ticks, directory, message, command, file error, warning. (Reason: These are primitive data variables, properties of a process, or UI text strings).

     * Discarded Verbs: exists, running, prompts, displays. (Reason: These describe simple UI text outputs or simple states/properties, rather than core architectural operations).

   * **Filter 3: A synonym already listed? (merge them)**

     * Merged Nouns: input file, setup. (Reason: 'Input file' is merged into the general file parsing logic; 'setup' is just a synonym for the creation process).

     * Merged Verbs: opens, closes, catches, encounters, ignores, continues. (Reason: These basic file-reading loop steps and error handling are merged into the overarching read and parse actions).

   * **Filter 4: Vague or whole system? (discard)**

      * Discarded Nouns: system, program. (Reason: Far too broad; they represent the entire application boundary, not a specific blueprint).

      * Discarded Verbs: starts, finishes, loops. (Reason: Too generic; they just describe the general flow of time or language constructs, not a specific domain job).

### 3. Surviving Classes and methods

   * Surviving Nouns (The Classes):

     * controller (becomes SimulationController)

     * process (becomes Process)

     * memory (becomes MemoryManager)

     * tracking list (becomes ReadyQueue)

   * Surviving Verbs (The Methods):

     * load, reads, parses, created, added.
   

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

