#include <iostream>
#include <limits>
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
    // Default constructor is used when a process is not found.
    Process() : processId(0), requiredRAM(0), totalCpuTicks(0), state("New") {}

    // Constructor and this pointer
    Process(int id, int ram, int ticks)
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

        if (selectedProcess.getId() == 0) {
            cout << "No process is available for execution.\n";
            return;
        }

        // Update the matching process stored by the controller rather than
        // changing only a temporary copy returned by the ready queue.
        for (Process& process : processes) {
            if (process.getId() == selectedProcess.getId()) {
                process.setState("Running");
                selectedProcess = process;
                break;
            }
        }

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

int readInteger(const string& prompt) {
    int value;

    while (true) {
        cout << prompt;
        if (cin >> value) {
            return value;
        }

        cout << "Invalid input. Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void displayMenu() {
    cout << "\n----------------------------------------\n";
    cout << "              CONTROL PANEL             \n";
    cout << "----------------------------------------\n";
    cout << "1. Create New Process\n";
    cout << "2. Allocate Memory for a Process\n";
    cout << "3. Deallocate Memory for a Process\n";
    cout << "4. Select Scheduler\n";
    cout << "5. Run Selected Scheduler\n";
    cout << "6. View Processes and System Status\n";
    cout << "7. Remove Process\n";
    cout << "8. Shutdown System\n";
    cout << "----------------------------------------\n";
}

void createProcess(SimulationController& controller) {
    int processId = readInteger("Enter process ID: ");
    int requiredRAM = readInteger("Enter required RAM (MB): ");
    int cpuTicks = readInteger("Enter required CPU ticks: ");

    if (processId <= 0 || requiredRAM < 0 || cpuTicks < 0) {
        cout << "Invalid process details. Process was not created.\n";
        return;
    }

    if (controller.findProcess(processId).getId() != 0) {
        cout << "A process with this ID already exists.\n";
        return;
    }

    Process process(processId, requiredRAM, cpuTicks);
    controller.addProcess(process);
    cout << "Process created successfully.\n";
}

void allocateMemory(SimulationController& controller) {
    int processId = readInteger("Enter process ID: ");
    Process process = controller.findProcess(processId);

    if (process.getId() == 0) {
        cout << "Process not found.\n";
        return;
    }

    controller.getMemoryManager().allocateMemory(process);
    cout << "Memory allocated successfully.\n";
    cout << "Free memory: "
         << controller.getMemoryManager().getFreeMemory() << " MB\n";
}

void deallocateMemory(SimulationController& controller) {
    int processId = readInteger("Enter process ID: ");
    Process process = controller.findProcess(processId);

    if (process.getId() == 0) {
        cout << "Process not found.\n";
        return;
    }

    controller.getMemoryManager().deallocateMemory(process);
    cout << "Memory deallocated successfully.\n";
    cout << "Free memory: "
         << controller.getMemoryManager().getFreeMemory() << " MB\n";
}

void selectScheduler(
    SimulationController& controller,
    FCFSscheduler& fcfs,
    SJFscheduler& sjf,
    PriorityScheduler& priority,
    RoundRobinScheduler& roundRobin) {

    cout << "\nSelect a scheduler:\n";
    cout << "1. First-Come, First-Served (FCFS)\n";
    cout << "2. Shortest Job First (SJF)\n";
    cout << "3. Priority Scheduling\n";
    cout << "4. Round Robin\n";

    int choice = readInteger("Enter scheduler choice: ");

    switch (choice) {
        case 1:
            controller.setScheduler(&fcfs);
            cout << "FCFS scheduler selected.\n";
            break;
        case 2:
            controller.setScheduler(&sjf);
            cout << "SJF scheduler selected.\n";
            break;
        case 3:
            controller.setScheduler(&priority);
            cout << "Priority scheduler selected.\n";
            break;
        case 4:
            controller.setScheduler(&roundRobin);
            cout << "Round Robin scheduler selected.\n";
            break;
        default:
            cout << "Invalid scheduler choice.\n";
    }
}

void viewSystemStatus(const SimulationController& controller) {
    controller.generateResults();
    cout << "Total processes created: "
         << Process::getTotalProcesses() << "\n";
}

void removeProcess(SimulationController& controller) {
    int processId = readInteger("Enter process ID to remove: ");
    Process process = controller.findProcess(processId);

    if (process.getId() == 0) {
        cout << "Process not found.\n";
        return;
    }

    controller.removeProcess(processId);
    cout << "Process removed successfully.\n";
}

void handleMenuChoice(
    int choice,
    SimulationController& controller,
    FCFSscheduler& fcfs,
    SJFscheduler& sjf,
    PriorityScheduler& priority,
    RoundRobinScheduler& roundRobin,
    bool& running) {

    switch (choice) {
        case 1:
            createProcess(controller);
            break;
        case 2:
            allocateMemory(controller);
            break;
        case 3:
            deallocateMemory(controller);
            break;
        case 4:
            selectScheduler(controller, fcfs, sjf, priority, roundRobin);
            break;
        case 5:
            controller.runSimulation();
            break;
        case 6:
            viewSystemStatus(controller);
            break;
        case 7:
            removeProcess(controller);
            break;
        case 8:
            cout << "Shutting down the simulator...\n";
            running = false;
            break;
        default:
            cout << "Invalid menu choice. Please select an option from 1 to 8.\n";
    }
}

int main() {
    cout << "=== Mini OS Simulator ===\n";

    SimulationController controller(1024);

    // Scheduler objects remain alive while the menu is running.
    FCFSscheduler fcfs(&controller.getReadyQueue());
    SJFscheduler sjf(&controller.getReadyQueue());
    PriorityScheduler priority(&controller.getReadyQueue());
    RoundRobinScheduler roundRobin(&controller.getReadyQueue(), 20);

    bool running = true;

    while (running) {
        displayMenu();

        try {
            int choice = readInteger("Enter your choice: ");
            handleMenuChoice(
                choice,
                controller,
                fcfs,
                sjf,
                priority,
                roundRobin,
                running);
        }
        catch (const OutOfMemoryException& exception) {
            cout << "Memory error: " << exception.what() << "\n";
        }
        catch (const QueueFullException& exception) {
            cout << "Queue error: " << exception.what() << "\n";
        }
        catch (const OSException& exception) {
            cout << "OS error: " << exception.what() << "\n";
        }
    }

    cout << "Simulator terminated successfully.\n";
    return 0;
}
