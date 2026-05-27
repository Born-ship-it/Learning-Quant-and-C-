# Project 4: Order Book Simulator

> **Concept:** Market microstructure & trade matching  
> **Key C++ skills:** STL containers (`std::map`, `std::priority_queue`), RAII, move semantics, C++17 structured bindings

---

## Overview

At the heart of any electronic exchange lies the limit order book—a real-time data structure that stores resting buy and sell orders and matches them when their prices cross. This project builds a **single-threaded limit order book** from scratch in modern C++. It supports adding limit orders, canceling orders, and automatically generating trades via price-time priority (first in, first out at each price level). By the end, you'll have a working simulation that can process a stream of orders and output the resulting trades.

The implementation emphasizes cache-friendly data layout, efficient price-level lookups, and safe resource management—skills directly transferable to high‑performance trading systems.

---

## Learning Objectives

- Design a realistic **order book data model** using STL containers
- Implement **price-time priority matching** with bid/ask aggregation
- Use **`std::map`** for logarithmic price-level insertion and deletion
- Apply **move semantics** to avoid unnecessary copying of order objects
- Write clean, testable components with **RAII** for order lifetime management
- Understand the difference between **marketable** and **resting** orders

---

## Prerequisites

- C++17 compiler (GCC 9+, Clang 7+, MSVC 2019+)
- CMake ≥ 3.16
- Standard library only (no external dependencies)

---

## Build & Run

```bash
cd project-04-order-book
cmake -B build
cmake --build build
./build/order_book      # On Windows: .\build\Debug\order_book.exe
