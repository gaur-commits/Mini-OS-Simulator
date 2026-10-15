#include <iostream>
#include "Process.h"
#include "Schedulers.h"
#include "SimulationController.h"

using namespace std;

int main() {
    cout << "=== OS Simulator Started ===\n";

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
