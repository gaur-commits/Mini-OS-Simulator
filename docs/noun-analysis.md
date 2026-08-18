# Noun-Verb Analysis

## Raw Candidate List (Nouns):
User, System, Process, Simulation, System Clock, OS Simulator program, input file, machine, Process objects, memory, controller, tracking list, terminal, file name, integers, ID, Memory Requirement, CPU Ticks, FileNotFoundException, management options, operation, information, scheduling algorithm, simulation results, main menu, configuration, RAM capacity, MemoryManager, SimulationController, InputMismatchException, ProcessControlBlock, Ready Queue, CPU state.

## Discarded Candidates & Filter Applied:
* **Filter 1 (Actors/ExternalEntities):** User, System Clock, System, OS Simulator program, machine, terminal. (Outside system boundaries).
* **Filter 2 (Attributes/Values):** ID, Memory Requirement, CPU Ticks, file name, integers, numbers, commas, information, RAM capacity, memory, CPU state. (These become the variables).
* **Filter 3 (Redundant/Synonyms):** Process objects, controller, tracking list, input file, Simulation. (Duplicate concepts).
* **Filter 4 (Actions/Events/UI):** FileNotFoundException, InputMismatchException, management options, operation, main menu, configuration, simulation results. (Errors or UI screens).

## Surviving Classes:
1. SimulationController
2. MemoryManager
3. Scheduler
4. Process
5. ProcessControlBlock
6. ReadyQueue
