# Project 5: Multithreaded Monte Carlo Pricer

> **Concept:** High‑performance parallel simulation  
> **Key C++ skills:** `std::thread`, `std::async`, `std::atomic`, mutexes, parallel algorithms (C++17), performance measurement

---

## Overview

The Monte Carlo engine from Project 3 works well, but its single‑threaded nature leaves the full power of modern multi‑core CPUs untapped. This project takes that engine and parallelizes it using C++’s threading facilities. By distributing simulation paths across multiple threads, we can dramatically reduce pricing latency—a crucial requirement for intraday risk calculations and real‑time decision support. The project compares the performance of different parallelization strategies (manual `std::thread`, `std::async`, and `std::atomic` accumulators) and reports the speedup achieved on your hardware.

---

## Learning Objectives

- Launch and join **`std::thread`** objects safely using RAII wrappers
- Accumulate a shared result with **`std::atomic`** without locks
- Use **`std::async`** and futures for a higher‑level parallelism model
- Avoid false sharing by carefully laying out thread‑local data
- Implement a simple **thread pool** (optional extension) for reusable worker threads
- Benchmark **speedup** and **efficiency** (speedup / number of cores) using `std::chrono`

---

## Prerequisites

- C++17 compiler (GCC 9+, Clang 7+, MSVC 2019+)
- CMake ≥ 3.16
- Standard library only (no external dependencies)
- A multi‑core CPU to observe real speedup

---

## Build & Run

```bash
cd project-05-multithreaded-pricer
cmake -B build
cmake --build build
./build/multithreaded_pricer   # On Windows: .\build\Debug\multithreaded_pricer.exe
