# Learning-Quant-and-C++
I will use this as my centre for learning quant and C++

*Good links*
Reddit forum wiki: https://www.reddit.com/r/quant/wiki/index/
# quant-finance-cpp

> From quantum information to quantitative finance — a structured, self-directed journey.

I'm a Quantum Information Science graduate (MSc, UCPH & DTU) with a strong background in mathematical modelling and algorithm development. After receiving candid feedback from a Head of Quant that I needed to **demonstrate genuine quant finance knowledge and C++ proficiency**, I started this repository to publicly document my learning.

This repo contains a series of small, focused C++ projects that bridge the gap between my quantum physics toolkit and the world of quantitative finance.

---

## Learning Objectives

- Master modern C++ (C++17/20) in a performance-critical context
- Implement foundational quant finance models from scratch
- Build a portfolio that proves my skills beyond a CV bullet point

---

## Project Roadmap

| # | Project | Concept | Key C++ Skills |
|---|---------|---------|----------------|
| 1 | Market Data Fetcher | S&P 500 data pipeline | CMake, HTTP requests, RAII, exception handling |
| 2 | Black-Scholes Pricer | Options pricing & Greeks | `constexpr`, lambdas, `<cmath>` |
| 3 | Monte Carlo Engine | Path-dependent pricing (Asian options) | RNG, `std::accumulate`, templates |
| 4 | Order Book Simulator | Market microstructure | STL containers, move semantics |
| 5+ | Extensions | Multithreaded pricer, volatility calibration | `std::thread`, parallel algorithms |

---

## Build & Run

Each project is self-contained inside its own directory with a `CMakeLists.txt`.

```bash
cd project-01-market-data
cmake -B build
cmake --build build
./build/market_data
