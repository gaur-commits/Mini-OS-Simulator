#include <iostream>
#include <string>
using namespace std;

// base class exception
class OSException {
protected:
    string message;
public:
    OSException(string msg) {
        message = msg;
    }
    string getMessage() {
        return message;
    }
};

// Deri1
class OutOfMemoryException : public OSException {
public:
    OutOfMemoryException() 
        : OSException("OutOfMemoryException: Not enough free RAM to allocate process") {}
};

// Deri2 - ready queue full
class QueueFullException : public OSException {
public:
    QueueFullException() 
        : OSException("QueueFullException: Ready Queue is completely full!") {}
};


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

class Scheduler {
public:
    virtual void printSchedulerType() = 0;
    virtual void executeProcess(Process* queue[], int count) = 0;
};

class FCFSScheduler : public Scheduler {
public:
    void printSchedulerType() override {
        cout << "[Scheduler] Running First-Come, First-Served (FCFS)\n";
    }
    void executeProcess(Process* queue[], int count) override {
        for (int i = 0; i < count; i++) {
            queue[i]->setState("Running");
            queue[i]->displayInfo();
            queue[i]->setState("Terminated");
        }
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
        
        if (!validateMemoryRequirement(size)) {
            throw OutOfMemoryException(); 
        }
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
        
        // if queue full, excep
        if (processCount >= 10) {
            throw QueueFullException();
        }

        // here...
        ram.allocateMemory(p->getId(), requiredRam);

        readyQueue[processCount] = p;
        processCount++;
        cout << "Process " << p->getId() << " added to Ready Queue.\n";
    }

    void setScheduler(Scheduler* newScheduler) {
        activeScheduler = newScheduler;
    }

    void runSimulation() {
        
        // if queue empty, no scheduler, base excep
        if (processCount == 0) {
            throw OSException("Simulation failed: Ready Queue is empty.");
        }
        if (activeScheduler == nullptr) {
            throw OSException("Simulation failed: No scheduler selected.");
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

    cout << "\n--- Starting Main Controller ---\n";
    SimulationController controller(1024); // We have 1024 MB total RAM

    Process p1(101, 50);
    Process p2(102, 30);
    Process p3(103, 40);

    // TRY BLOCK
    try {
        controller.addProcessToQueue(&p1, 256); // Uses 256 MB, also less
        controller.addProcessToQueue(&p2, 128); // Uses 128 MB, less than total
        
        //asking for more, outofmemexcept.
        controller.addProcessToQueue(&p3, 2000); 
    } 
    
    catch (OutOfMemoryException e) {
        cout << "[Caught Derived Exception] " << e.getMessage() << "\n";
    } 
    catch (QueueFullException e) {
        cout << "[Caught Derived Exception] " << e.getMessage() << "\n";
    } 
        
    catch (OSException e) {
        cout << "[Caught Base Exception] " << e.getMessage() << "\n";
    }
    
    try {
        FCFSScheduler fcfs;
        controller.setScheduler(&fcfs);
        controller.runSimulation();
    } 
    catch (OSException e) {
        cout << "[Caught Base Exception] " << e.getMessage() << "\n";
    }

    return 0;
}
