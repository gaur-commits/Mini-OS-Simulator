#include <iostream>
using namespace std;

class LegacyProcess {
public:
    int oldId;
    int oldTicks;
    LegacyProcess(int id, int ticks) {
        oldId = id;
        oldTicks = ticks;
    }
};

class Process {
protected:
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

    Process(int defaultTicks) {
        this->processId = 999; 
        this->cpuTicks = defaultTicks;
        this->state = "Ready";
        totalProcesses++;
    }

    Process(LegacyProcess oldProcess) {
        this->processId = oldProcess.oldId;
        this->cpuTicks = oldProcess.oldTicks;
        this->state = "Ready";
        totalProcesses++;
    }

    operator int() {
        return cpuTicks;
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

    static int getTotalProcesses() {
        return totalProcesses;
    }
}; 
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
        : Process(id, ticks), PriorityProcess(id, ticks, priority), BackgroundProcess(id, ticks) {}
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
        freeMemory -= size;
        cout << "[Memory] Allocated " << size << " MB for Process " << processId << ". Free: " << freeMemory << " MB\n";
    }

    void deallocateMemory(int processId, int size) {
        freeMemory += size;
        if (freeMemory > totalMemory) freeMemory = totalMemory;
        cout << "[Memory] Freed " << size << " MB from Process " << processId << ". Free: " << freeMemory << " MB\n";
    }
};

class SimulationController {
private:
    MemoryManager ram;
    Scheduler* activeScheduler;
    Process* readyQueue[10];
    int processCount;

public:
    SimulationController(int totalRam) : ram(totalRam) {
        activeScheduler = nullptr;
        processCount = 0;
    }

    bool validateRequest(int requiredRam) {
        return ram.validateMemoryRequirement(requiredRam);
    }

    void addProcessToQueue(Process* p, int requiredRam) {
        if (processCount < 10 && validateRequest(requiredRam)) {
            ram.allocateMemory(p->getId(), requiredRam);
            readyQueue[processCount] = p;
            processCount++;
            cout << "Process " << p->getId() << " added to Ready Queue.\n";
        } else {
            cout << "Failed to add Process " << p->getId() << ". Out of memory or queue full.\n";
        }
    }

    void setScheduler(Scheduler* newScheduler) {
        activeScheduler = newScheduler;
    }

    void runSimulation() {
        if (processCount == 0) {
            cout << "Simulation failed: Ready Queue is empty.\n";
            return;
        }
        if (activeScheduler == nullptr) {
            cout << "Simulation failed: No scheduler selected.\n";
            return;
        }

        cout << "\n--- Starting Main Simulation Loop ---\n";
        activeScheduler->printSchedulerType();
        
        activeScheduler->executeProcess(readyQueue, processCount);
        
        cout << "--- Simulation Complete ---\n";
    }
};

template <typename T>
void systemLog(T message) {
    cout << ">> [LOG]: " << message << "\n";
}

int main() {
    cout << "=== OS Simulator Started ===\n";

    Process autoProcess = 50; 
    
    LegacyProcess oldP(101, 30);
    Process modernProcess = oldP; 

    int remainingTime = autoProcess; 

    
    systemLog("Typecasting tests completed."); 
    systemLog(remainingTime);                  
    systemLog(3.14);

    cout << "\n---Starting Main Controller---\n";
    SimulationController controller(1024); 

    Process p1(101, 50);
    Process p2(102, 30);
    
    controller.addProcessToQueue(&p1, 256);
    controller.addProcessToQueue(&p2, 128);

    FCFSScheduler fcfs;
    controller.setScheduler(&fcfs);

    controller.runSimulation();

    return 0;
}
