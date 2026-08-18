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
* **Use Case Name:** Manage Simulation
* **Primary Actor:** User
* **Stakeholders:**
  * User (wants to control and modify the current simulation).
  * System (needs to maintain a valid and consistent simulation state).
* **Preconditions:**
  * OS Simulator program is started and is running.
  * The simulation has been initialized with at least one process.
* **Postconditions:**
  * The requested changes to the simulation are applied.
  * If the operation is cancelled or invalid, the simulation remains unchanged.
* **Trigger:** User selects the "Manage Simulation" command in the terminal.

### Main Flow

1. The Simulation User selects the "Manage Simulation" option.
2. The System displays the available management options.
3. The Simulation User selects an operation, such as viewing, modifying, or removing a process.
4. The System asks the user to enter the required information.
5. The Simulation User provides the required information.
6. The System validates the request.
7. The System applies the requested change to the simulation.
8. The System displays the updated simulation information.

### Alternate Flow 1: Selected Process Does Not Exist

6a. The System cannot find the specified process.
7a. The System displays an error message: "Error: Process not found."
8a. The System returns to the management options without changing the simulation.

### Alternate Flow 2: User Cancels the Operation

4b. The Simulation User selects the "Cancel" option.
5b. The System discards the current operation.
6b. The System returns to the simulation management screen without changing the simulation.

## 3. Run Simulation

* **Use Case Name:** Run Simulation
* **Primary Actor:** User
* **Stakeholders:**
  * User (wants to observe how the selected scheduling algorithm handles the processes).
  * System (needs valid processes and a scheduling algorithm to execute the simulation).
* **Preconditions:**
  * At least one process has been created.
  * A scheduling algorithm has been selected.
* **Postconditions:**
  * The simulation is completed.
  * The simulation results are available for the user to view.
* **Trigger:** User selects the "Run Simulation" command in the terminal.

### Main Flow

1. The Simulation User selects the "Run Simulation" option.
2. The System checks that valid processes are available.
3. The System checks that a scheduling algorithm has been selected.
4. The System runs the simulation using the selected scheduling algorithm.
5. The System generates the simulation results.
6. The System displays the results to the Simulation User.

### Alternate Flow 1: No Processes Are Available

2a. The System finds that no processes have been created.
3a. The System displays a message: "No processes available. Please create at least one process."
4a. The System returns to the main menu.

### Alternate Flow 2: No Scheduling Algorithm Has Been Selected

3b. The System finds that no scheduling algorithm has been selected.
4b. The System asks the Simulation User to select a scheduling algorithm.
5b. The Simulation User selects a scheduling algorithm.
6b. The System resumes the simulation from step 4 of the main flow.

## 4. Select Scheduling Algorithm

* **Use Case Name:** Select Scheduling Algorithm
* **Primary Actor:** User
* **Stakeholders:**
  * User (wants to choose the scheduling method that will be used to run the simulation).
  * System (needs a valid scheduling algorithm to execute the simulation).
* **Preconditions:**
  * OS Simulator program is started and is running.
  * The user has access to the simulation configuration.
* **Postconditions:**
  * A valid scheduling algorithm is selected and associated with the current simulation.
* **Trigger:** User selects the "Select Scheduling Algorithm" command in the terminal.

### Main Flow

1. The Simulation User selects the "Select Scheduling Algorithm" option.
2. The System displays the scheduling algorithms available in the simulator.
3. The Simulation User selects a scheduling algorithm.
4. The System checks whether the selected algorithm is valid.
5. The System stores the selected algorithm as the scheduling method for the current simulation.
6. The System informs the Simulation User that the scheduling algorithm has been selected.

### Alternate Flow 1: Invalid Selection

4a. The System determines that the selected option is invalid.
5a. The System displays an error message: "Error: Invalid scheduling algorithm."
6a. The System displays the available scheduling algorithms again.
7a. The Simulation User selects a valid algorithm.
8a. The System continues from step 4 of the main flow.

### Alternate Flow 2: User Cancels Selection

2b. The Simulation User selects the "Cancel" option.
3b. The System keeps the previously selected algorithm, if any.
4b. The System returns to the simulation configuration screen.

### Alternate Flow 3: No Algorithm Available

2c. The System finds that no scheduling algorithms are currently available.
3c. The System displays a message: "No scheduling algorithms available."
4c. The System returns to the simulation configuration screen.

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

## 5. Pause Simulation

* **Use Case Name:** Pause Simulation
* **Primary Actor:** User
* **Stakeholders:**
  * User (wants to temporarily stop the simulation and continue it later).
  * System (needs to preserve the current state of the simulation).
* **Preconditions:**
  * A simulation has been started and is currently running.
* **Postconditions:**
  * The simulation is paused.
  * The current state of the simulation is preserved so that it can be resumed.
* **Trigger:** User selects the "Pause Simulation" command while a simulation is running.

### Main Flow

1. The Simulation User selects the "Pause Simulation" option.
2. The System checks whether the simulation is currently running.
3. The System temporarily stops the simulation.
4. The System preserves the current state of the simulation.
5. The System changes the simulation status to **Paused**.
6. The System informs the Simulation User that the simulation has been paused.

### Alternate Flow 1: Simulation Is Not Running

2a. The System determines that the simulation is not currently running.
3a. The System displays a message: "Simulation cannot be paused because it is not running."
4a. The System returns to the current screen without changing the simulation state.

### Alternate Flow 2: Simulation Already Completed

2b. The System determines that the simulation has already completed.
3b. The System displays a message: "A completed simulation cannot be paused."
4b. The System keeps the simulation results unchanged.

