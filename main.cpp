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
