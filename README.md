# Shatranj One

A chess platform built around a custom C++ chess engine,
with online gameplay and game-analysis features planned.

## Tech Stack

- C++17
- CMake
- MinGW-w64 (GCC)
- GoogleTest
- React (planned)
- Node.js (planned)

## Prerequisites

- CMake 3.20 or newer
- A C++17-compatible compiler
- MinGW Makefiles build tool
- Internet access for the initial GoogleTest download

## Build

Configure the project:

```powershell
cmake -S engine -B engine/build -G "MinGW Makefiles"