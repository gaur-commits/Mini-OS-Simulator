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
