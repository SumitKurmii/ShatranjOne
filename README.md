# ShatranjOne

ShatranjOne is a chess engine project built in C++ with CMake and GoogleTest.

## Build

### Windows

From the repository root:

```bash
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

The same CTest command works in Bash on Linux and macOS.

The current test suite contains 10 tests covering the Position system.
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
- [ ] FEN parsing
- [ ] Legal move generation and perft
- [ ] Search and UCI protocol
- [ ] Web application and game analysis
Progress
Position System
- [x] Created Position class
- [x] Split Position implementation into position.h and position.cpp
- [x] Added 64-square board representation
- [x] Added Color enum
- [x] Added Piece enum
- [x] Added Square enum
- [x] Added piece encoding
- [x] Added side-to-move state
- [x] Added castling rights
- [x] Added en-passant target square
- [x] Added half-move and full-move counters
- [x] Added position reset functionality
- [x] Added basic GoogleTest coverage
- [x] Added invalid-square handling
- [x] Verified tests are discovered and executed by CTest
- [x] Verified a deliberately failing test is correctly detected
- [x] Verified all 10 Position tests pass
Build & Testing
- [x] CMake build configured
- [x] GoogleTest integrated
- [x] CTest configured
- [x] CI workflow configured
- [x] Engine builds successfully
- [x] Test suite passes successfully