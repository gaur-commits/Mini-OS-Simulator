# Mini OS Simulator

A small operating-system simulator written in **C++ (OOP)** with a simple **HTML / CSS / JavaScript** frontend.
The C++ program runs a tiny web server, and the web page talks to it, so the browser buttons call real C++ classes.

## Features

- Add processes with an ID, required RAM and CPU ticks
- Choose a scheduler for each process: **FCFS, SJF, Priority, Round Robin**
- Run the simulation and see which scheduler each process uses
- Free memory is tracked and updated live
- C++ exceptions (`OutOfMemoryException`, `QueueFullException`) are shown as red messages on the page

> The schedulers demonstrate polymorphism by reporting their own name. They do not implement real scheduling algorithms.

## Project structure

```
Mini-OS-Simulator/
└── Mini-OS-Web/
    ├── backend/
    │   ├── main.cpp      C++ classes + web server
    │   └── httplib.h     cpp-httplib (single-header web server library)
    └── frontend/
        ├── index.html    page structure
        ├── style.css     page styling
        └── script.js     sends requests to the C++ server
```

`backend` and `frontend` must stay side by side, because the server looks for the `../frontend` folder.

## How to run

1. Open a terminal in the `Mini-OS-Web/backend` folder.
2. Compile:

   **Mac / Linux**
   ```
   g++ main.cpp -o server -std=c++17 -pthread
   ```
   **Windows (MinGW)**
   ```
   g++ main.cpp -o server.exe -std=c++17 -lws2_32 -lwsock32
   ```
3. Start the server (run it from inside `backend`):

   **Mac / Linux**
   ```
   ./server
   ```
   **Windows**
   ```
   server.exe
   ```
4. Open **http://localhost:8080** in your browser.

If you change `main.cpp`, stop the server (Ctrl+C), recompile and run it again. If you only change HTML, CSS or JS, just refresh the browser.

## How it works

| Page action | Request | C++ code that runs |
|---|---|---|
| Click **Add Process** | `POST /add` | `allocateMemory()` then `addProcess()` |
| Click **Run Simulation** | `GET /run` | `runSimulation()` |

The server replies with plain text. `script.js` reads the reply and updates the table, free memory and log box.

## OOP concepts used

- Classes and objects, constructors, `this` pointer
- Inheritance (`PriorityProcess`, scheduler subclasses, exception hierarchy)
- Polymorphism: virtual and pure virtual functions (`Scheduler::getName()`, `pickNextProcess()`)
- Custom exception classes with `try` / `catch`
- Operator overloading (`<<`) with a friend function
- Method overloading (`displayInfo`)
- Static members and static functions
- Nested class (`Scheduler::Info`)
- Pointers to base class and object slicing

## Tech used

C++17, [cpp-httplib](https://github.com/yhirose/cpp-httplib), HTML, CSS, JavaScript (`fetch`)
