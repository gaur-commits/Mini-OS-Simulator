#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

// User-defined exception
class OSException : public exception {
protected:
    string message;

public:
    OSException(const string& message) : message(message) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

// User-defined exception
class OutOfMemoryException : public OSException {
public:
    OutOfMemoryException() : OSException("Not enough free memory.") {}
};

// User-defined exception
class QueueFullException : public OSException {
public:
    QueueFullException() : OSException("Ready queue is full.") {}
};

class Process {
private:
    int processId;
    int requiredRAM;
    int totalCpuTicks;
    string state;
    static int totalProcesses; // Static variable

public:
    // Constructor and this pointer
    Process(int id = 0, int ram = 0, int ticks = 0)
        : processId(id), requiredRAM(ram), totalCpuTicks(ticks), state("New") {
        totalProcesses++;
    }

    // Method overloading
    void displayInfo() const {
        cout << *this << endl;
    }

    // Method overloading
    void displayInfo(bool detailed) const {
        cout << *this;
        if (detailed) {
            cout << " | Detailed view enabled";
        }
        cout << endl;
    }

    int getId() const { return processId; }
    int getRequiredRAM() const { return requiredRAM; }
    int getTotalCpuTicks() const { return totalCpuTicks; }
    string getState() const { return state; }

    void setState(const string& newState) {
        this->state = newState; // this pointer
    }

    static int getTotalProcesses() { // Static function
        return totalProcesses;
    }

    // Friend stream operator overloading
    friend ostream& operator<<(ostream& output, const Process& process);
};

int Process::totalProcesses = 0;

// Stream operator overloading
ostream& operator<<(ostream& output, const Process& process) {
    output << "Process ID: " << process.processId
           << " | RAM: " << process.requiredRAM << " MB"
           << " | CPU Ticks: " << process.totalCpuTicks
           << " | State: " << process.state;
    return output;
}

// Inheritance demonstration for object slicing
class PriorityProcess : public Process {
private:
    int priority;

public:
    PriorityProcess(int id, int ram, int ticks, int priority)
        : Process(id, ram, ticks), priority(priority) {}

    int getPriority() const { return priority; }
};

class ReadyQueue {
private:
    vector<Process> queue;
    static const int MAX_SIZE = 10;

public:
    void addProcess(const Process& process) {
        if (queue.size() >= MAX_SIZE) {
            throw QueueFullException(); // throw
        }
        queue.push_back(process);
    }

    void removeProcess(int processId) {
        for (auto it = queue.begin(); it != queue.end(); ++it) {
            if (it->getId() == processId) {
                queue.erase(it);
                return;
            }
        }
    }

    Process findProcess(int processId) const {
        for (const Process& process : queue) {
            if (process.getId() == processId) {
                return process;
            }
        }
        return Process();
    }

    bool containsProcess(int processId) const {
        return findProcess(processId).getId() != 0;
    }

    Process getNextProcess() const {
        if (!queue.empty()) {
            return queue.front();
        }
        return Process();
    }

    void reorder() {
        // Reserved for future scheduling logic.
    }

    bool empty() const { return queue.empty(); }
};

class MemoryManager {
private:
    int totalMemory;
    int freeMemory;
    int allocatedMemory;

public:
    MemoryManager(int total)
        : totalMemory(total), freeMemory(total), allocatedMemory(0) {}

    bool validateMemoryRequirement(const Process& process) const {
        return process.getRequiredRAM() <= freeMemory;
    }

    void allocateMemory(const Process& process) {
        if (!validateMemoryRequirement(process)) {
            throw OutOfMemoryException(); // throw
        }

        freeMemory -= process.getRequiredRAM();
        allocatedMemory += process.getRequiredRAM();
    }

    void deallocateMemory(const Process& process) {
        freeMemory += process.getRequiredRAM();
        allocatedMemory -= process.getRequiredRAM();

        if (freeMemory > totalMemory) {
            freeMemory = totalMemory;
        }
    }

    int getFreeMemory() const { return freeMemory; }
};

class Scheduler {
protected:
    ReadyQueue* readyQueue; // Pointer to object

public:
    // Nested class
    class Info {
    private:
        string schedulerName;

    public:
        Info(const string& name) : schedulerName(name) {}
        string getName() const { return schedulerName; }
    };

    Scheduler(ReadyQueue* queue) : readyQueue(queue) {}
    virtual ~Scheduler() = default; // Virtual function

    virtual bool checkAvailability() const { // Virtual function
        return readyQueue != nullptr && !readyQueue->empty();
    }

    virtual Process pickNextProcess() = 0; // Pure virtual function

    virtual double calculateWaitingTime() const { return 0.0; }
    virtual double calculateTurnaroundTime() const { return 0.0; }
};

class FCFSscheduler : public Scheduler {
public:
    FCFSscheduler(ReadyQueue* queue) : Scheduler(queue) {}

    Process pickNextProcess() override { // Inheritance and overriding
        return readyQueue->getNextProcess();
    }
};

class SJFscheduler : public Scheduler {
public:
    SJFscheduler(ReadyQueue* queue) : Scheduler(queue) {}

    Process pickNextProcess() override { // Inheritance and overriding
        return readyQueue->getNextProcess();
    }
};

class PriorityScheduler : public Scheduler {
public:
    PriorityScheduler(ReadyQueue* queue) : Scheduler(queue) {}

    Process pickNextProcess() override { // Inheritance and overriding
        return readyQueue->getNextProcess();
    }
};

class RoundRobinScheduler : public Scheduler {
private:
    int timeQuantum;

public:
    RoundRobinScheduler(ReadyQueue* queue, int quantum)
        : Scheduler(queue), timeQuantum(quantum) {}

    Process pickNextProcess() override { // Inheritance and overriding
        return readyQueue->getNextProcess();
    }
};

class SimulationController {
private:
    vector<Process> processes;
    string simulationState;
    ReadyQueue readyQueue;
    MemoryManager memoryManager;
    Scheduler* scheduler; // Pointer to base class

public:
    SimulationController(int totalMemory)
        : simulationState("Created"),
          memoryManager(totalMemory),
          scheduler(nullptr) {}

    void addProcess(const Process& process) {
        processes.push_back(process);
        readyQueue.addProcess(process);
    }

    void removeProcess(int processId) {
        for (auto it = processes.begin(); it != processes.end(); ++it) {
            if (it->getId() == processId) {
                processes.erase(it);
                break;
            }
        }
        readyQueue.removeProcess(processId);
    }

    Process findProcess(int processId) const {
        for (const Process& process : processes) {
            if (process.getId() == processId) {
                return process;
            }
        }
        return Process();
    }

    bool validateSimulationRequest(const Process& process) const {
        return process.getId() != 0 &&
               process.getRequiredRAM() >= 0 &&
               process.getTotalCpuTicks() >= 0;
    }

    void updateSimulationState() {
        simulationState = "Running";
    }

    void runSimulation() {
        updateSimulationState();

        if (scheduler == nullptr || !scheduler->checkAvailability()) {
            cout << "No scheduler or process is available.\n";
            return;
        }

        Process selectedProcess = scheduler->pickNextProcess();
        selectedProcess.setState("Running");
        cout << "Selected process: " << selectedProcess << endl;
    }

    void generateResults() const {
        cout << "\nSimulation State: " << simulationState << endl;
        cout << "Free Memory: " << memoryManager.getFreeMemory() << " MB\n";

        for (const Process& process : processes) {
            process.displayInfo(true);
        }
    }

    void setScheduler(Scheduler* selectedScheduler) {
        scheduler = selectedScheduler;
    }

    ReadyQueue& getReadyQueue() { return readyQueue; }
    MemoryManager& getMemoryManager() { return memoryManager; }
};

int main() {
    cout << "=== Mini OS Simulator ===\n\n";

    SimulationController controller(1024);

    Process process1(101, 200, 50);
    Process process2(102, 150, 30);

    // Object slicing demonstration
    PriorityProcess priorityProcess(103, 100, 20, 1);
    Process slicedProcess = priorityProcess;
    cout << "Sliced process: " << slicedProcess << "\n\n";

    try { // try
        controller.addProcess(process1);
        controller.addProcess(process2);
        controller.addProcess(priorityProcess);

        FCFSscheduler fcfs(&controller.getReadyQueue());
        Scheduler* schedulerPointer = &fcfs; // Pointer to derived object
        controller.setScheduler(schedulerPointer);

        controller.getMemoryManager().allocateMemory(process1);
        controller.getMemoryManager().allocateMemory(process2);

        controller.runSimulation();
        controller.generateResults();

        controller.getMemoryManager().deallocateMemory(process1);
        controller.getMemoryManager().deallocateMemory(process2);
    }
    catch (const OutOfMemoryException& exception) { // Derived catch
        cout << "Memory error: " << exception.what() << endl;
    }
    catch (const OSException& exception) { // Base catch
        cout << "OS error: " << exception.what() << endl;
    }

    cout << "\nTotal processes created: "
         << Process::getTotalProcesses() << endl;

    return 0;
}
