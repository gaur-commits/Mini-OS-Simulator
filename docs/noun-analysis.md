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

## Use Case 2: Manage Simulation - Combined Noun & Verb Analysis

### 1. Raw Candidate List

**Candidate Nouns:** user, simulation user, system, simulation, process, operation, management option, information, required information, request, change, simulation management screen, command, terminal, error message, updated simulation information, current operation.

**Candidate Verbs:** selects, displays, viewing, modifying, removing, asks, enter, provides, validates, applies, changes, cancels, discards, returns, find, exists, initialized, running.

### 2. Noun and Verb filtering

- **Filter 1: Outside the system? (actor not class)**

  - Discarded Nouns: user, simulation user, terminal. (Reason: The user is an external actor interacting with the simulator, while the terminal is the external interface through which the interaction takes place).
  - Discarded Verbs: selects, enter, provides. (Reason: These are actions performed by the human user, not operations performed by the system).

- **Filter 2: A property of something else? (attribute not class)**

  - Discarded Nouns: management option, information, required information, change, command, error message, updated simulation information, current operation. (Reason: These represent input data, output information, temporary state, or details associated with a simulation operation rather than independent objects).
  - Discarded Verbs: displays, asks, returns. (Reason: These mainly describe user-interface/output behavior rather than operations representing independent domain responsibilities).

- **Filter 3: A synonym already listed? (merge them)**

  - Merged Nouns: simulation user → user. (Reason: Both refer to the same actor interacting with the simulator).
  - Merged Verbs: viewing → displays, modifying → changes, removing → changes. (Reason: These represent specific forms of displaying or changing the state of a process/simulation and do not need separate representations as duplicate concepts).
  - Merged Verbs: discards → cancels. (Reason: Discarding the current operation is the result of cancelling it).

- **Filter 4: Vague or whole system? (discard)**

  - Discarded Nouns: system, operation, request. (Reason: These are too broad or generic to represent specific objects in the simulation model).
  - Discarded Verbs: running, exists, initialized. (Reason: These describe the state or lifecycle of the simulation rather than a specific operation that should become a method).

### 3. Surviving Classes and methods

- **Surviving Nouns (The Classes):**

  - simulation (becomes `Simulation`)
  - process (becomes `Process`)

- **Surviving Verbs (The Methods):**

  - validates
  - applies
  - changes
  - displays
  - cancels
  - find

## Use Case 3: Run Simulation - Combined Noun & Verb Analysis

### 1. Raw Candidate List

**Candidate Nouns:** user, simulation user, system, simulation, process, scheduling algorithm, algorithm, method, simulation results, results, command, terminal, option, message, main menu, simulation configuration.

**Candidate Verbs:** selects, checks, available, created, selected, runs, executes, generates, displays, observes, view, finds, asks, returns, resumes, continues.

### 2. Noun and Verb filtering

- **Filter 1: Outside the system? (actor not class)**

  - Discarded Nouns: user, simulation user, terminal. (Reason: The user is an external actor interacting with the simulator, while the terminal is the external interface through which the interaction takes place).
  - Discarded Verbs: selects, observes, view. (Reason: These are actions performed by the human user rather than operations performed by the simulator).

- **Filter 2: A property of something else? (attribute not class)**

  - Discarded Nouns: command, option, message, simulation results, results, main menu, simulation configuration. (Reason: These represent user-interface elements, output data, or information/state associated with the simulation rather than independent objects).
  - Discarded Verbs: displays, asks, returns. (Reason: These mainly describe user-interface or control-flow behavior rather than core simulation operations).

- **Filter 3: A synonym already listed? (merge them)**

  - Merged Nouns: algorithm, method → scheduling algorithm. (Reason: Both refer to the scheduling method selected for executing the simulation).
  - Merged Nouns: simulation results, results → results. (Reason: Both refer to the output produced after running the simulation).
  - Merged Verbs: executes → runs. (Reason: Executing the simulation and running the simulation represent the same operation).
  - Merged Verbs: finds, available → checks. (Reason: These describe the process of checking whether the required processes or scheduling algorithm are available).

- **Filter 4: Vague or whole system? (discard)**

  - Discarded Nouns: system, simulation. (Reason: System represents the whole application, while simulation is too broad if it is being treated as the overall system operation rather than a specific domain object).
  - Discarded Verbs: continues, resumes, created, selected. (Reason: These mainly describe the state or flow of an operation rather than specific responsibilities that should become methods).

### 3. Surviving Classes and methods

- **Surviving Nouns (The Classes):**

  - process (becomes `Process`)
  - scheduling algorithm (becomes `SchedulingAlgorithm`)

- **Surviving Verbs (The Methods):**

  - checks
  - runs
  - generates



