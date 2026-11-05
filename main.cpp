#include <iostream>
#include <string>
#include <thread>   
#include <mutex>    
#include <chrono>   
using namespace std;

mutex printMutex;
void print(const string &text) {
    lock_guard<mutex> lock(printMutex); 
    cout << text << endl;
}

class OSException {
protected:
    string message;
public:
    OSException(string msg) { message = msg; }
    virtual ~OSException() = default;
    const string &getMessage() const { return message; }
};

class OutOfMemoryException : public OSException {
public:
    OutOfMemoryException()
        : OSException("Not enough free RAM to allocate process.") {}
};

class QueueFullException : public OSException {
public:
    QueueFullException()
        : OSException("Ready Queue is completely full!") {}
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

    static int getTotalProcesses() { return totalProcesses; }
};
int Process::totalProcesses = 0;

class MemoryManager {
private:
    int totalMemory;
    int freeMemory;
    mutex memoryMutex; 

public:
    MemoryManager(int total) {
        this->totalMemory = total;
        this->freeMemory = total;
    }

    void allocateMemory(int processId, int size) {
        lock_guard<mutex> lock(memoryMutex); 
        if (size > freeMemory) {
            throw OutOfMemoryException();
        }
        freeMemory -= size;
        print("[Memory] Allocated " + to_string(size) + " MB for Process " + to_string(processId) +
              ". Free: " + to_string(freeMemory) + " MB");
    }

    void deallocateMemory(int processId, int size) {
        lock_guard<mutex> lock(memoryMutex);
        freeMemory += size;
        if (freeMemory > totalMemory) freeMemory = totalMemory;
        print("[Memory] Freed " + to_string(size) + " MB from Process " + to_string(processId) +
              ". Free: " + to_string(freeMemory) + " MB");
    }
};

class Scheduler {
public:
    virtual ~Scheduler() = default;
    virtual void printSchedulerType() = 0;
    virtual void executeProcess(Process *queue[], int count) = 0;
};

class FCFSScheduler : public Scheduler {
public:
    void printSchedulerType() override {
        cout << "[Scheduler] Running First-Come, First-Served (FCFS)\n";
    }
    void executeProcess(Process *queue[], int count) override {
        for (int i = 0; i < count; i++) {
            queue[i]->setState("Running");
            queue[i]->displayInfo();
            queue[i]->setState("Terminated");
        }
    }
};

void changeState(Process *p, const string &newState) {
    p->setState(newState);
    print("[Process " + to_string(p->getId()) + "] State: " + newState);
}

void runProcess(Process *p, MemoryManager *mem, int ramNeeded) {
    try {
        changeState(p, "New");
        mem->allocateMemory(p->getId(), ramNeeded); 

        changeState(p, "Ready");
        this_thread::yield(); 

        changeState(p, "Running");
        this_thread::sleep_for(chrono::milliseconds(50)); 

        changeState(p, "Waiting");
        this_thread::sleep_for(chrono::milliseconds(50)); 

        changeState(p, "Terminated");
        mem->deallocateMemory(p->getId(), ramNeeded);
    }
    catch (const OSException &e) {
        changeState(p, "Aborted"); 
        print("[Thread Error] Process " + to_string(p->getId()) + " Failed: " + e.getMessage());
    }
}

class Runnable {
public:
    virtual ~Runnable() = default;
    virtual void run() = 0;
};

class ProcessTask : public Runnable {
    Process *process;
    MemoryManager *memory;
    int ram;
public:
    ProcessTask(Process *p, MemoryManager *m, int r) : process(p), memory(m), ram(r) {}
    void run() override { runProcess(process, memory, ram); }
};

int main() {
    cout << "=== OS Simulator Started ===\n\n";

    cout << "--- PHASE 1: Typecasting Tests ---\n";
    Process autoProcess = 50;           
    LegacyProcess oldP(101, 30);
    Process modernProcess = oldP;       
    int remainingTime = autoProcess;    
    cout << "Typecasting tests passed successfully.\n\n";

    cout << "--- PHASE 2: Sequential FCFS Execution ---\n";
    MemoryManager sequentialRam(1024);
    Process p1(101, 50);
    Process p2(102, 30);
    Process *readyQueue[2] = {&p1, &p2};
    
    FCFSScheduler fcfs;
    fcfs.printSchedulerType();
    fcfs.executeProcess(readyQueue, 2);
    cout << "\n";


    cout << "--- PHASE 3: Multithreaded Asynchronous Execution ---\n";
    cout << "Testing Mutex Locks & Concurrent Resource Allocation\n\n";
    
    MemoryManager concurrentRam(500); 
    Process worker1(301, 3);
    Process worker2(302, 3);
    Process worker3(303, 3);

    // Thread 1: Standard function
    thread t1(runProcess, &worker1, &concurrentRam, 200);

    // Thread 2: Standard function
    thread t2(runProcess, &worker2, &concurrentRam, 200);

    // Thread 3: Runnable Interface (Will trigger OutOfMemoryException because 200+200+200 > 500)
    ProcessTask task(&worker3, &concurrentRam, 200);
    thread t3(&ProcessTask::run, &task);

    t1.join();
    t2.join();
    t3.join();

    cout << "\n=== OS Simulator Complete ===\n";
    cout << "Total processes created during simulation: " << Process::getTotalProcesses() << "\n";
    
    return 0;
}
