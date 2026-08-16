# Use Case specifications

## 1. Create Process
* **Use Case Name:** Create Process
* **Primary Actor:** User
* **Stakeholders:**
  * User (wants to add a process to the simulation).
  * System (needs valid process data to run the system clock).
* **Preconditions:**
  * OS Simulator program is started and is running.
  * Properly formatted input file (input.txt) exists on the machine.
* **Postconditions:**
  * Multiple Process objects are created in the system's memory
  * Processes are added to the controller's tracking list, ready for scheduling
* **Trigger:** User selects the "Load Process" command in the terminal.

### Main Flow

1. The Simulation User selects the option to load a process file.
2. The System prompts the user to enter the file name.
3. The Simulation User inputs input.txt.
4. The System opens the file and reads it line by line.
5. For each line, the System parses the integers and creates a new Process object with its ID, Memory Requirement, and CPU Ticks.
6. The System closes the file and displays a message: "Processes loaded successfully."  

### Alternate Flow 1: File Not Found

3a. The Simulation User inputs a file name that does not exist in the directory.  
4a. The System catches a FileNotFoundException and displays an error: "Error: File not found."  
5a. The System loops back to step 2 and prompts the user to enter the file name again.  

### Alternate Flow 2: Invalid Data Format

5b. The System encounters a line in the text file with letters instead of numbers, or missing commas.  
6b. The System displays a warning: "Invalid data on line X. Skipping process."  
7b. The System ignores that specific line, continues reading the rest of the valid lines to create the remaining processes, and finishes the setup.  

## 2. Manage Simulation

Use Case	                      Manage Simulation
Primary Actor	                  User
Stakeholders	User —            wants to control and modify the current simulation
Preconditions	                  The simulator is running.
Postconditions	                The requested changes to the simulation are applied, or the simulation remains unchanged if the operation is cancelled or invalid.
Trigger	                        User selects Manage Simulation.

Main Flow

User selects Manage Simulation.
System displays the available management options.
User selects an operation, such as viewing, modifying or removing a process.
System asks for the required information.
User provides the required information.
System validates the request.
System applies the requested change.
System displays the updated simulation information.
Alternate Flows

A1. Selected process does not exist

At step 6, the system cannot find the specified process.
System displays an error message.
System returns to the management options.

A2. User cancels the operation

At step 4 or 5, the user selects Cancel.
System discards the current operation.
System returns to the simulation management screen without changing the simulation.

## 3.  Run Simulation

Use Case	                                Run Simulation
Primary Actor	                            User
Stakeholders                              User wants to observe how the selected scheduling algorithm handles the processes
Preconditions	                            At least one process has been created and a scheduling algorithm has been selected.
Postconditions	                          The simulation is completed and the results are available for the user to view.
Trigger	                                  User selects Run Simulation.

Main Flow

User selects Run Simulation.
System checks that valid processes are available.
System checks that a scheduling algorithm has been selected.
System runs the simulation using the selected scheduling algorithm.
System generates the simulation results.
System displays the results to the user.
Alternate Flows

A1. No processes are available

At step 2, the system finds that no processes have been created.
System displays a message asking the user to create at least one process.
System returns to the main menu.

A2. No scheduling algorithm has been selected

At step 3, the system finds that no scheduling algorithm has been selected.
System asks the user to select a scheduling algorithm.
User selects an algorithm.
System resumes the simulation from step 4 of the main flow.

## 4. Configure Simulation
* **Use Case Name:** Configure Simulation
* **Primary Actor:** User
* **Stakeholders:**
  * User (wants to easily setup the system parameters like RAM before starting the simulation).
  * System (needs valid hardware constraints in order to simulate the environment).
* **Preconditions:**
  * OS Simulator program is launched.
* **Postconditions:**
  * System parameters (e.g total RAM) are available and stored in the SimulationController.
* **Trigger:** User selects the "Configure Simulation" command in the terminal.

### Main Flow

1. The User selects the "Configure Simulation" command.
2. The System prompts the User to enter the total RAM capacity for the simulated system (e.g., "Enter total RAM in MB:").
3. The User inputs a valid positive integer (e.g. 1024).
4. The System instantiates the MemoryManager with the provided RAM capacity.
5. The System displays a success message: "Simulation configured successfully. Total RAM set to 1024 MB."
   
### Alternate Flow 1: File Not Found

3a. The User inputs non-numeric characters (e.g., typing "one thousand" instead of 1000).  
4a. The System catches an InputMismatchException and displays an error: "Error: Invalid input. Please enter numerical digits only."  
5a. The System loops back to step 2 and prompts the User to enter the total RAM capacity again.    

### Alternate Flow 2: Invalid Data Format

3b. The User inputs a negative number or zero (e.g., -500 or 0).  
4b. The System detects the invalid boundary and displays an error: "Error: System RAM must be greater than 0 MB."  
5b. The System loops back to step 2 and prompts the User to enter the total RAM capacity again.

## 7: Perform Context Switch
* **Use Case Name:** Perform Context Switch
* **Primary Actor:** System Clock
* **Stakeholders:**
  * System Clock (needs to accurately trigger the swap when the time limit hits).
  * Simulation System / Scheduler (needs to fairly rotate CPU time among apps).
  * Process (needs its exact progress saved so it doesn't lose its work).
* **Preconditions:**
  * The simulation loop is actively running.
  * A Process is currently in the RUNNING state occupying the CPU.
* **Postconditions:**
  * The currently running process is safely paused and its progress is saved in a ProcessControlBlock.
  * The next process in line is loaded and changed to the RUNNING state.
* **Trigger:** The System Clock reaches the maximum time quantum limit (e.g., 5 ticks have passed).

### Main Flow:
1. The System Clock signals the Controller that the current time quantum has expired.
2. The Scheduler pauses the currently RUNNING process.
3. The System takes a snapshot of the process's remaining ticks and saves it in an immutable ProcessControlBlock.
4. The System updates the paused process's state to READY and moves it to the back of the Ready Queue.
5. The Scheduler pulls the next Process from the front of the Ready Queue.
6. The System updates the newly pulled process's state to RUNNING and loads its saved ProcessControlBlock data.
7. The System Clock resets its quantum timer, and execution begins on the new process.
  
### Alternate Flow 1: Process Finishes Early
1a. The currently RUNNING process completes its final required CPU tick before the System Clock quantum expires.  
2a. The System updates the finished process's state to TERMINATED.  
3a. The MemoryManager is notified to free the RAM allocated to that specific process.  
4a. The Scheduler skips saving a ProcessControlBlock (since the process is dead) and directly pulls the next process from the queue (Returns to Main Flow Step 5).

### Alternate Flow 2: Ready Queue is Empty
5a. The Scheduler attempts to pull the next process, but the Ready Queue is completely empty.  
6a. The System sets the CPU state to IDLE.  
7a. The System Clock continues to tick forward, checking for new processes to arrive or waiting for the simulation to end. 

