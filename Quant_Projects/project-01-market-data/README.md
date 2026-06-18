# Project 1: Market Data Fetcher

> **Concept:** Real-world financial data pipeline  
> **Key C++ skills:** CMake, libcurl, RAII, exception handling, C++17

---

## Overview

This project fetches historical S&P 500 index data from a free web API and saves it to a local JSON file. It serves as the foundation for any quantitative analysis pipeline—without data, there's nothing to model.

The program demonstrates safe resource management in C++, robust error handling, and basic networking, all built with CMake for cross-platform compatibility.

---

## Learning Objectives

- Set up a modern C++ project with **CMake**
- Use **libcurl** to perform HTTP GET requests
- Implement **RAII** (Resource Acquisition Is Initialization) for automatic cleanup of resources
- Handle runtime errors gracefully with **exceptions**
- Write clean, portable code following the **C++17** standard

---

## Prerequisites

- **C++17 compiler** (GCC 9+, Clang 7+, MSVC 2019+)
- **CMake** (version 3.16 or higher)
- **libcurl** (development libraries)

### Installing libcurl on Windows
Using vcpkg (recommended):
```bash
vcpkg install curl:x64-windows
```
Then pass the toolchain file to CMake:
```bash
cmake -B build -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake
```
Build & Run
```bash
cd project-01-market-data
cmake -B build
cmake --build build
./build/market_data   # On Windows: .\build\Debug\market_data.exe
```
