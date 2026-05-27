# Project 2: Black-Scholes Option Pricer

> **Concept:** Options pricing & Greeks  
> **Key C++ skills:** `constexpr`, lambdas, `<cmath>`, smart pointers, C++17

---

## Overview

This project implements the Black-Scholes-Merton model from scratch to price European call and put options and compute their "Greeks"—the partial derivatives that measure sensitivity to underlying parameters. The entire calculation is expressed using compile-time `constexpr` functions where possible, demonstrating how to push computation to compile time for zero-cost runtime performance. A lightweight `Option` struct and a pricing function are the core, while a lambda-based Greek calculator shows functional-style C++ in action.

---

## Learning Objectives

- Derive and code the **Black-Scholes formula** in C++
- Use **`constexpr` functions** for compile-time evaluation
- Apply **C++17 lambdas** to implement Greek calculations cleanly
- Manage parameters with a **struct** and **smart pointers** (if extended)
- Practice **numerical stability** (handling edge cases like zero volatility or extreme moneyness)

---

## Prerequisites

- C++17 compiler (GCC 9+, Clang 7+, MSVC 2019+)
- CMake ≥ 3.16
- Standard library only (no external dependencies)

---

## Build & Run

```bash
cd project-02-black-scholes
cmake -B build
cmake --build build
./build/black_scholes      # On Windows: .\build\Debug\black_scholes.exe
