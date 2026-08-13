# Use Case specifications

## 1. Create Process
Use Case	                  Create Process
Primary                     Actor	User
Stakeholders	User          wants to add a process to the simulation
Preconditions	              The simulator is running and the user is on the process management screen.
Postconditions	            A new valid process is created and added to the list of processes.
Trigger	                    User selects the Create Process option.

Main Flow

User selects Create Process.
System asks the user to enter process details.
User enters the required details, such as process name, arrival time, burst time and priority.
System validates the entered details.
System creates the process.
System adds the process to the current simulation.
System displays a confirmation to the user.

Alternate Flows

A1. Selected process does not exist

At step 6, the system cannot find the specified process.
System displays an error message.
System returns to the management options.

A2. User cancels the operation

At step 4 or 5, the user selects Cancel.
System discards the current operation.
System returns to the simulation management screen without changing the simulation.

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
