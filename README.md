# Shatranj One

A chess platform built around a custom C++ chess engine, with online gameplay and game analysis planned.

## Current Status

The project currently has:

- A working C++17/CMake build.
- GoogleTest and CTest integration.
- Reproducible builds from a fresh clone.
- GitHub Actions CI for Debug and Release builds on Ubuntu.
- CI verification through an intentionally failing test.

Chess functionality is not implemented yet. The next milestone is board/position representation.

## Tech Stack

- C++17
- CMake
- MinGW-w64 (GCC)
- GoogleTest
- GitHub Actions
- React (planned)
- Node.js (planned)

## Prerequisites

- CMake 3.20 or newer
- A C++17-compatible compiler
- A compatible build tool
- Internet access for the initial GoogleTest download

## Build on Windows (MSYS2 UCRT64)

Ensure `C:\msys64\ucrt64\bin` is on your PATH, then run these commands in PowerShell from the repository root:

```powershell
cmake -S engine -B engine/build -G "MinGW Makefiles"
cmake --build engine/build

Build on Linux or macOS
With a C++ compiler and CMake installed, run from the repository root:
cmake -S engine -B engine/build
cmake --build engine/build

Run the Engine
Windows:
.\engine\build\shatranj-one.exe

Linux or macOS:
./engine/build/shatranj-one

Run Tests
From the repository root:
ctest --test-dir engine/build --output-on-failure

The same CTest command works in Bash on Linux and macOS.
Continuous Integration
GitHub Actions runs the C++ engine build and tests on every push and pull request to main.
The CI matrix currently covers:
- Debug
- Release
The workflow configures, builds, and runs CTest on ubuntu-latest.
The CI pipeline has also been verified to fail when the test suite contains an intentional failure.
Roadmap
- [x] Repository and build system
- [x] Initial C++ executable
- [x] GoogleTest integration
- [x] GitHub Actions CI
- [ ] Board representation and position state
- [ ] FEN parsing
- [ ] Legal move generation and perft
- [ ] Search and UCI protocol
- [ ] Web application and game analysis