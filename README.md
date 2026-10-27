# ShatranjOne

A chess engine written in C++ with CMake, GoogleTest, CTest, and GitHub Actions CI.

## Build

### Windows

From the repository root:

```powershell
cmake -S engine -B engine/build -G "MinGW Makefiles"
cmake --build engine/build

Linux or macOS
With a C++ compiler and CMake installed:
cmake -S engine -B engine/build
cmake --build engine/build

Run the Engine
Windows
.\engine\build\shatranj-one.exe

Linux or macOS
./engine/build/shatranj-one

Run Tests
From the repository root:
ctest --test-dir engine/build --output-on-failure

The test suite currently contains 20 tests covering position state and FEN parsing/validation.
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
- [x] Board representation and position state
- [x] FEN parsing and validation
- [ ] Legal move generation and perft
- [ ] Search and UCI protocol
- [ ] Web application and game analysis
Progress
Position System
- [x] Created Position class
- [x] Added 64-square board representation
- [x] Added piece encoding
- [x] Added side-to-move state
- [x] Added castling rights
- [x] Added en-passant target square
- [x] Added half-move and full-move counters
- [x] Added position reset functionality
- [x] Added basic GoogleTest coverage
- [x] Verified tests are discovered and executed by CTest
FEN
- [x] Parse board position
- [x] Parse side to move
- [x] Parse castling rights
- [x] Parse en-passant target square
- [x] Parse half-move clock
- [x] Parse full-move number
- [x] Validate invalid piece characters
- [x] Validate invalid side-to-move field
- [x] Validate invalid castling rights
- [x] Validate invalid en-passant square
- [x] Validate invalid move counters
- [x] Validate malformed FEN input
Build & Testing
- [x] CMake build configured
- [x] GoogleTest integrated
- [x] CTest configured
- [x] 20/20 tests passing
- [x] CI workflow configured