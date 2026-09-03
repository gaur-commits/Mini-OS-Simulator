#include <iostream>
#include <string>

using namespace std;

// 1. ENCAPSULATION
class Process {
private:
    int processId;
    int cpuTicks; // Time needed to execute
    string state;

    // 2. FRIEND FUNCTION
    friend void printProcessInfo(Process p); 

public:
    // 3. CONSTRUCTOR OVERLOADING (Compile-Time Polymorphism)
    Process(int id, int ticks) {
        processId = id;
        cpuTicks = ticks;
        state = "Ready";
    }

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

    // 7. OPERATOR OVERLOADING (Compile-Time Polymorphism)
    bool operator<(Process& otherProcess) {
        return this->cpuTicks < otherProcess.cpuTicks;
    }
};

// FRIEND FUNCTION IMPLEMENTATION
void printProcessInfo(Process p) {
    cout << "DEBUG -> Process ID: " << p.processId 
         << " | CPU Ticks: " << p.cpuTicks 
         << " | State: " << p.state << endl;
}

// 4. ABSTRACTION
class Scheduler {
public:
    // Pure Virtual Function 
    virtual void executeProcess(Process* p) = 0; 
};

// 5. HIERARCHICAL INHERITANCE
// Child 1 inheriting from Scheduler
class FCFSScheduler : public Scheduler {
public:
    // 6. METHOD OVERRIDING (Run-Time Polymorphism)
    void executeProcess(Process* p) override {
        cout << "[FCFS Scheduler] First-Come, First-Served picking Process " << p->getId() << "..." << endl;
        p->setState("Running");
        cout << ">> Process " << p->getId() << " state changed to: " << p->getState() << endl;
    }
};

class SJFScheduler : public Scheduler {
public:
    // 6. METHOD OVERRIDING (Run-Time Polymorphism)
    void executeProcess(Process* p) override {
        cout << "[SJF Scheduler] Shortest-Job-First picking Process " << p->getId() << "..." << endl;
        p->setState("Running");
        cout << ">> Process " << p->getId() << " state changed to: " << p->getState() << endl;
    }
};

// MAIN
int main() {
    cout << "--- OS Simulator Initialized ---\n" << endl;

    // 1. Testing Constructor Overloading
    Process p1(101, 50);                 // Uses Constructor A
    Process p2(102, 10, "Waiting");      // Uses Constructor B

    // 2. Testing Friend Function
    printProcessInfo(p1);
    printProcessInfo(p2);
    cout << endl;

    // Testing Operator Overloading
    cout << "--- Testing Operator Overloading ---" << endl;
    if (p2 < p1) { 
        cout << ">> Process " << p2.getId() << " is shorter and should run first in SJF!\n" << endl;
    }

    // 3. Testing Run-Time Polymorphism using Pointers
    
    // Create the specific algorithm objects
    FCFSScheduler fcfsAlgo;      
    SJFScheduler sjfAlgo;        

    // Create our single Base Pointer (The "Universal Remote")
    Scheduler* coreScheduler;       
    
    // --- RUNNING FCFS ---
    coreScheduler = &fcfsAlgo;           // Point to FCFS
    coreScheduler->executeProcess(&p1);  // Pass the memory address of p1

    cout << endl;

    // --- RUNNING SJF ---
    coreScheduler = &sjfAlgo;            // Switch pointer to SJF
    coreScheduler->executeProcess(&p2);  // Pass the memory address of p2

    cout << "\n--- OS Simulator Shutdown ---" << endl;
    return 0;
}
