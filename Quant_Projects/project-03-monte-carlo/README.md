# Project 3: Monte Carlo Engine

> **Concept:** Path-dependent pricing via stochastic simulation  
> **Key C++ skills:** Random number generation, `std::accumulate`, templates, C++17 `<random>`, performance analysis

---

## Overview

Many exotic options—like Asian, barrier, or lookback options—have no closed-form solution. Monte Carlo simulation is the workhorse method for pricing these path-dependent derivatives. This project builds a generic Monte Carlo engine in C++ that simulates an arbitrary number of asset price paths under the risk-neutral Geometric Brownian Motion model, prices an Asian call option, and examines how the result converges as the number of simulations increases.

By designing the engine with templates, it can be easily extended to other payoff types and stochastic processes—a key requirement in real-world quant libraries.

---

## Learning Objectives

- Generate high-quality pseudo-random numbers with C++17's `<random>` library
- Simulate asset price paths using the **Euler–Maruyama discretization** of Geometric Brownian Motion
- Compute the payoff of a **path-dependent** Asian option (arithmetic average strike)
- Apply the **law of large numbers** to obtain a price estimate and a confidence interval
- Design a **template-based Monte Carlo engine** that separates the model, the payoff, and the simulation loop
- Profile and compare runtime for different numbers of paths

---

## Prerequisites

- C++17 compiler (GCC 9+, Clang 7+, MSVC 2019+)
- CMake ≥ 3.16
- Standard library only (no external dependencies)

---

## Build & Run

```bash
cd project-03-monte-carlo
cmake -B build
cmake --build build
./build/monte_carlo      # On Windows: .\build\Debug\monte_carlo.exe
