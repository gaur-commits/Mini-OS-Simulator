#include <iostream>
#include <string>
using namespace std;

class Process {
private:
    int processId;
    int cpuTicks; 
    string state;
    static int totalProcesses;
    
public:
    Process(int id, int ticks) {
        processId = id;
        cpuTicks = ticks;
        state = "Ready";
        totalProcesses++;
    }

    Process(int id, int ticks, string startState) {
        processId = id;
        cpuTicks = ticks;
        state = startState;
        totalProcesses++;
    }

    int getId() { return processId; }
    int getTicks() { return cpuTicks; }
    string getState() { return state; }
    void setState(string newState) { state = newState; }

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

    static int getTotalProcesses() {
        return totalProcesses;
    }

    friend bool operator<(const Process& p1, const Process& p2);
    friend ostream& operator<<(ostream& out, const Process& p);
}; 

bool operator<(const Process& p1, const Process& p2) {
    return p1.cpuTicks < p2.cpuTicks;
}
ostream& operator<<(ostream& out, const Process& p) {
    out << "Process ID: " << p.processId 
        << " | Ticks: " << p.cpuTicks 
        << " | State: " << p.state;
    return out;
}
int Process::totalProcesses = 0;

class Scheduler {
public:
    class Info {
        public:
            string algorithmName;
            void show() {
                cout << "Algorithm in use: " << algorithmName << endl;
            }
        };
    virtual void executeProcess(Process& p) = 0; 
};

class FCFSScheduler final: public Scheduler {
public:
    void executeProcess(Process& p) override {
        cout << "\n[FCFS] Executing Process " << p.getId() << "..." << endl;
        p.setState("Running");
        cout << "Status Updated: Process " << p.getId() << " is now " << p.getState() << endl;
    }
};

class SJFScheduler final: public Scheduler {
public:
    void executeProcess(Process& p) override {
        cout << "\n[SJF] Executing Shortest Process " << p.getId() << "..." << endl;
        p.setState("Running");
        cout << "Status Updated: Process " << p.getId() << " is now " << p.getState() << endl;
    }
};

int main() {
    cout << "--- Starting OS Simulation ---\n" << endl;

    Process p1(101, 50);                 
    Process p2(102, 10, "Waiting");      

    p1.displayInfo();
    p2.displayInfo();

    cout << "\nChecking burst times for SJF..." << endl;
    if (p2 < p1) {   
        cout << "Process " << p2.getId() << " has fewer ticks than Process " << p1.getId() << endl;
    }

    FCFSScheduler fcfs;      
    SJFScheduler sjf;        
    
    fcfs.executeProcess(p1); 
    sjf.executeProcess(p2); 

    cout << "\n--- Simulation Ended ---" << endl;
    return 0;
}
