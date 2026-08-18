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
