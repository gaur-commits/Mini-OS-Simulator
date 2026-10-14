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
       this->processId = id;
        this->cpuTicks = ticks;
        this->state = "Ready";
        totalProcesses++;
    }

    Process(int id, int ticks, string startState) {
       this->processId = id;
        this->cpuTicks = ticks;
        this->state = startState;
        totalProcesses++;
    }

    int getId() { return processId; }
    int getTicks() { return cpuTicks; }
    string getState() { return state; }
    void setState(string newState) { this->state = newState; }

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

class PriorityProcess : virtual public Process {
protected:
    int priorityLevel;
public:
    PriorityProcess(int id, int ticks, int priority) : Process(id, ticks) {
        this->priorityLevel = priority;
    }
};

class BackgroundProcess : virtual public Process {
public:
    BackgroundProcess(int id, int ticks) : Process(id, ticks) {}
};

class SystemProcess : public PriorityProcess, public BackgroundProcess {
public:
    SystemProcess(int id, int ticks, int priority) 
        : Process(id, ticks), PriorityProcess(id, ticks, priority), BackgroundProcess(id, ticks) {
    }
};
class Scheduler {
public:
    class Info {
        public:
            string algorithmName;
            void show() {
                cout << "Algorithm in use: " << algorithmName << endl;
            }
        };
    virtual void printSchedulerType() {
        cout << "Generic OS Scheduler" << endl;
    }
    virtual void executeProcess(Process& p) = 0; 
};

class FCFSScheduler final: public Scheduler {
public:
    void executeProcess(Process& p) override {
        cout << "\n[FCFS] Executing Process " << p.getId() << "..." << endl;
        p.setState("Running");
    }
    void printSchedulerType() override {
        cout << "First-Come-First-Served (FCFS) Scheduler" << endl;
    }
};

class SJFScheduler final: public Scheduler {
public:
    void executeProcess(Process& p) override {
        cout << "\n[SJF] Executing Shortest Process " << p.getId() << "..." << endl;
        p.setState("Running");
    }
    void printSchedulerType() override {
        cout << "Shortest-Job-First (SJF) Scheduler" << endl;
    }
};

class PriorityScheduler final: public Scheduler {
public:
    void executeProcess(Process& p) override {
        cout << "\n[Priority] Executing Process " << p.getId() << " based on priority..." << endl;
        p.setState("Running");
    }
    void printSchedulerType() override {
        cout << "Priority Scheduler" << endl;
    }
};

class RoundRobinScheduler final: public Scheduler {
private:
    int timeQuantum; 
public:
    RoundRobinScheduler(int quantum = 10) {
        this->timeQuantum = quantum;
    }
    void executeProcess(Process& p) override {
        cout << "\n[Round Robin] Executing Process " << p.getId() 
             << " for a time slice of " << timeQuantum << " ticks..." << endl;
        p.setState("Running");
    }
    void printSchedulerType() override {
        cout << "Round Robin Scheduler (Quantum: " << timeQuantum << ")" << endl;
    }
};

class MemoryManager {
private:
    int totalMemory;
    int freeMemory;

public:
    MemoryManager(int total) {
        this->totalMemory = total;
        this->freeMemory = total;
    }

    bool validateMemoryRequirement(int size) {
        return size <= freeMemory;
    }

    void allocateMemory(int processId, int size) {
        if (validateMemoryRequirement(size)) {
            freeMemory -= size;
            cout << "[Memory] Allocated " << size << " MB for Process " << processId 
                 << ". Free memory: " << freeMemory << " MB" << endl;
        } else {
            cout << "[Memory] Allocation FAILED for Process " << processId << endl;
        }
    }

    void deallocateMemory(int processId, int size) {
        freeMemory += size;
        if (freeMemory > totalMemory) freeMemory = totalMemory;
        cout << "[Memory] Deallocated " << size << " MB from Process " << processId 
             << ". Free memory: " << freeMemory << " MB" << endl;
    }
};


int main() {
    MemoryManager ram(1024); 
    
    FCFSScheduler fcfs;      
    SJFScheduler sjf;
    PriorityScheduler priority;
    RoundRobinScheduler rr(20); 
    
    Scheduler* activeScheduler = nullptr; 
    
    Process* processQueue[10];
    int processCount = 0;

    int choice = 0;

    cout << "=== OS Simulator Initialized (1024 MB RAM) ===\n";

    while (choice != 5) {
        cout << "\n--- OS Control Panel ---\n";
        cout << "1. Create New Process\n";
        cout << "2. Allocate Memory for a Process\n";
        cout << "3. Select & Run Scheduler\n";
        cout << "4. View Total Processes\n";
        cout << "5. Shutdown System\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            if (processCount < 10) {
                int id, ticks;
                cout << "Enter Process ID (e.g., 101): ";
                cin >> id;
                cout << "Enter CPU Ticks required: ";
                cin >> ticks;
                
                processQueue[processCount] = new Process(id, ticks);
                cout << "[System] Process " << id << " created successfully.\n";
                processCount++;
            } else {
                cout << "[System] Queue full! Cannot create more processes.\n";
            }
        } 
        else if (choice == 2) {
            int id, size;
            cout << "Enter Process ID: ";
            cin >> id;
            cout << "Enter Memory Size (MB): ";
            cin >> size;
            ram.allocateMemory(id, size);
        } 
        else if (choice == 3) {
            if (processCount == 0) {
                cout << "[System] No processes to run! Create one first.\n";
                continue;
            }

            int algoChoice;
            cout << "Select Algorithm (1=FCFS, 2=SJF, 3=Priority, 4=RoundRobin): ";
            cin >> algoChoice;

            if (algoChoice == 1) activeScheduler = &fcfs;
            else if (algoChoice == 2) activeScheduler = &sjf;
            else if (algoChoice == 3) activeScheduler = &priority;
            else if (algoChoice == 4) activeScheduler = &rr;
            else {
                cout << "Invalid scheduler choice.\n";
                continue;
            }

            activeScheduler->printSchedulerType();
            
            Process* pToRun = processQueue[processCount - 1];
            activeScheduler->executeProcess(*pToRun);
        }
        else if (choice == 4) {
            cout << "Total Processes Created: " << Process::getTotalProcesses() << "\n";
            for (int i = 0; i < processCount; i++) {
                processQueue[i]->displayInfo();
            }
        }
    }

    cout << "\n[System] Shutting down... cleaning up memory.\n";
    for (int i = 0; i < processCount; i++) {
        delete processQueue[i];
    }

    return 0;
}
