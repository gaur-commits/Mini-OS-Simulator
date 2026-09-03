#include <iostream>
#include <string>

using namespace std;

// Class demonstrating Encapsulation (private data, public methods)
class Process {
private:
    int processId;
    int cpuTicks; 
    string state;

public:
    // Constructor Overloading
    // 1st Constructor: Normal process
    Process(int id, int ticks) {
        processId = id;
        cpuTicks = ticks;
        state = "Ready";
    }

    // 2nd Constructor: Process with a custom starting state
    Process(int id, int ticks, string startState) {
        processId = id;
        cpuTicks = ticks;
        state = startState;
    }

    // Getters & Setters
    int getId() { return processId; }
    int getTicks() { return cpuTicks; }
    string getState() { return state; }
    void setState(string newState) { state = newState; }

    // Operator Overloading for SJF comparison
    bool operator<(Process& otherProcess) {
        return this->cpuTicks < otherProcess.cpuTicks;
    }

    // Simple display method instead of a friend function
    void displayInfo() {
        cout << "Process ID: " << processId 
             << " | Ticks: " << cpuTicks 
             << " | State: " << state << endl;
    }

    void displayInfo(bool showDetailed) {
        if (showDetailed) {
            cout << "Process ID: " << processId 
                 << " | Ticks: " << cpuTicks 
                 << " | State: " << state << " (Detailed View)" << endl;
        } else {
            displayInfo(); 
        }
    }
};

// Abstract Base Class
class Scheduler {
public:
    // Pure Virtual Function (Abstraction)
    virtual void executeProcess(Process& p) = 0; 
};

// Hierarchical Inheritance - Child 1
class FCFSScheduler : public Scheduler {
public:
    // Method Overriding
    void executeProcess(Process& p) override {
        cout << "\n[FCFS] Executing Process " << p.getId() << "..." << endl;
        p.setState("Running");
        cout << "Status Updated: Process " << p.getId() << " is now " << p.getState() << endl;
    }
};

// Hierarchical Inheritance - Child 2
class SJFScheduler : public Scheduler {
public:
    // Method Overriding
    void executeProcess(Process& p) override {
        cout << "\n[SJF] Executing Shortest Process " << p.getId() << "..." << endl;
        p.setState("Running");
        cout << "Status Updated: Process " << p.getId() << " is now " << p.getState() << endl;
    }
};

int main() {
    cout << "--- Starting OS Simulation ---\n" << endl;

    // 1. Testing Constructor Overloading
    Process p1(101, 50);                 
    Process p2(102, 10, "Waiting");      

    // Display initial states
    p1.displayInfo();
    p2.displayInfo();

    // 2. Testing Operator Overloading
    cout << "\nChecking burst times for SJF..." << endl;
    if (p2 < p1) { 
        cout << "Process " << p2.getId() << " has fewer ticks than Process " << p1.getId() << endl;
    }

    // 3. Testing Inheritance & Method Overriding
    FCFSScheduler fcfs;      
    SJFScheduler sjf;        
    
    // Running FCFS Algorithm directly
    fcfs.executeProcess(p1); 

    // Running SJF Algorithm directly
    sjf.executeProcess(p2); 

    cout << "\n--- Simulation Ended ---" << endl;
    return 0;
}
