#include <iostream>
#include <string>
#include <thread>   // std::thread, sleep_for, yield
#include <mutex>    // std::mutex, std::lock_guard
#include <chrono>   // milliseconds
using namespace std;

// ---------- THREAD CHEAT SHEET ----------
// start -> run -> sleep -> yield -> join -> terminated
// Life cycle: New -> Ready -> Running -> Waiting -> Terminated
// ----------------------------------------

// ---------- SYNCHRONIZATION HELPER (used by all threads) ----------
// Without a mutex, two threads can use cout (or change a variable) at the
// same time and the result gets mixed up. This is called a race condition.
mutex printMutex;
void print(const string &text) {
    lock_guard<mutex> lock(printMutex);   // lock now, auto-unlock at end of function
    cout << text << endl;
}

// base class exception
class OSException {
protected:
    string message;
public:
    OSException(string msg) {
        message = msg;
    }
    virtual ~OSException() = default;
    const string &getMessage() const {
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

class MemoryManager {
private:
    int totalMemory;
    int freeMemory;
    mutex memoryMutex;   // SYNCHRONIZATION: protects freeMemory (shared by all threads)

public:
    MemoryManager(int total) {
        this->totalMemory = total;
        this->freeMemory = total;
    }

    bool validateMemoryRequirement(int size) {
        lock_guard<mutex> lock(memoryMutex);
        return size <= freeMemory;
    }

    void allocateMemory(int processId, int size) {
        lock_guard<mutex> lock(memoryMutex);   // only one thread can be here at a time
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

class SimulationController {
private:
    MemoryManager ram;
    Scheduler *activeScheduler;
    Process *readyQueue[10];
    int processCount;

public:
    SimulationController(int totalRam) : ram(totalRam) {
        activeScheduler = nullptr;
        processCount = 0;
    }

    MemoryManager &getMemoryManager() {
        return ram;
    }

    bool validateRequest(int requiredRam) {
        return ram.validateMemoryRequirement(requiredRam);
    }

    void addProcessToQueue(Process *p, int requiredRam) {

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

    void setScheduler(Scheduler *newScheduler) {
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

// =====================================================================
//                       MULTITHREADING SECTION
// =====================================================================

// ---------- THREAD LIFE CYCLE ----------
// The Process "state" string is the thread state. Every change is printed.
void changeState(Process *p, const string &newState) {
    p->setState(newState);
    print("[Process " + to_string(p->getId()) + "] State: " + newState);
}

// ---------- THE WORK EVERY THREAD DOES (this is the "run" code) ----------
// New -> Ready -> Running -> Waiting -> Terminated
void runProcess(Process *p, MemoryManager *mem, int ramNeeded) {
    try {
        changeState(p, "New");
        mem->allocateMemory(p->getId(), ramNeeded);   // shared resource (mutex inside)

        changeState(p, "Ready");
        this_thread::yield();                         // yield(): let other threads run first

        changeState(p, "Running");
        this_thread::sleep_for(chrono::milliseconds(50));   // sleep(): pretend to use the CPU

        changeState(p, "Waiting");
        this_thread::sleep_for(chrono::milliseconds(50));   // sleep(): pretend to wait for I/O

        changeState(p, "Terminated");
        mem->deallocateMemory(p->getId(), ramNeeded);
    }
    catch (const OSException &e) {
        // A thread must catch its own exceptions, otherwise the program crashes.
        print("[Thread Error] " + e.getMessage());
    }
}

// ---------- WAY 1: Thread with a normal function ----------
// (written in main: thread t1(runProcess, ...))

// ---------- WAY 2: Extending the Thread class ----------
class MyThread {                       // our own simple "Thread" class
    thread t;
public:
    virtual ~MyThread() { join(); }
    virtual void run() = 0;            // child class writes the work here
    void start() { t = thread(&MyThread::run, this); }   // start() launches run()
    void join() { if (t.joinable()) t.join(); }          // join() waits for the end
};

class ProcessThread : public MyThread {
    Process *process;
    MemoryManager *memory;
    int ram;
public:
    ProcessThread(Process *p, MemoryManager *m, int r) : process(p), memory(m), ram(r) {}
    void run() override { runProcess(process, memory, ram); }
};

// ---------- WAY 3: Implementing the Runnable interface ----------
class Runnable {                       // interface: only says "there is a run()"
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

// =====================================================================

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

    catch (const OutOfMemoryException &e) {
        cout << "[Caught Derived Exception] " << e.getMessage() << "\n";
    }
    catch (const QueueFullException &e) {
        cout << "[Caught Derived Exception] " << e.getMessage() << "\n";
    }

    catch (const OSException &e) {
        cout << "[Caught Base Exception] " << e.getMessage() << "\n";
    }

    try {
        FCFSScheduler fcfs;
        controller.setScheduler(&fcfs);
        controller.runSimulation();
    }
    catch (const OSException &e) {
        cout << "[Caught Base Exception] " << e.getMessage() << "\n";
    }

    // =================================================================
    //                    MULTITHREADING DEMO
    // =================================================================
    cout << "\n=== Multithreading Demo ===\n";
    MemoryManager *mem = &controller.getMemoryManager();

    Process worker1(301, 3);
    Process worker2(302, 3);
    Process worker3(303, 3);

    // WAY 1: normal function  ->  create the thread, it starts immediately
    thread t1(runProcess, &worker1, mem, 100);

    // WAY 2: extend Thread class  ->  call start() to begin
    ProcessThread t2(&worker2, mem, 50);
    t2.start();

    // WAY 3: Runnable interface  ->  give run() to a std::thread
    ProcessTask task(&worker3, mem, 30);
    thread t3(&ProcessTask::run, &task);

    // join(): main waits here until every thread has finished
    t1.join();
    t2.join();
    t3.join();

    cout << "=== All threads finished ===\n";
    cout << "Total processes created: " << Process::getTotalProcesses() << "\n";
    cout << "=== OS Simulator Complete ===\n";
    return 0;
}
