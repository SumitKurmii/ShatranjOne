# ShatranjOne

A chess engine written in C++17, with CMake, GoogleTest, CTest, and GitHub Actions CI. The long-term goal is to build a full-stack chess platform around the custom engine.

## Tech Stack

- C++17
- CMake
- GoogleTest
- CTest
- GitHub Actions CI
- React (planned)
- Node.js (planned)

## Build

### Windows

From the repository root:

```powershell
cmake -S engine -B engine/build -G "MinGW Makefiles"
cmake --build engine/build
```

### Linux or macOS

With a C++ compiler and CMake installed:

```bash
cmake -S engine -B engine/build
cmake --build engine/build
```

## Run the Engine

### Windows

```powershell
.\engine\build\shatranj-one.exe
```

### Linux or macOS

```bash
./engine/build/shatranj-one
```

## Run Tests

From the repository root:

```bash
ctest --test-dir engine/build --output-on-failure
```

**Latest reported local result: 81/81 tests passing.**

This result was reported after the latest Position and FEN changes. The latest test-suite revision has not yet been independently verified in CI.

## Continuous Integration

GitHub Actions CI was configured for the C++ engine.

The reported workflow covers:
- Debug
- Release

The workflow configures, builds, and runs CTest on `ubuntu-latest` for pushes and pull requests to `main`.

The CI pipeline was also reported to have been tested with an intentional failure to verify that failing tests make the workflow fail.

The latest 81-test revision still needs CI verification.

## Roadmap

- [x] Repository and build system
- [x] Initial C++ executable
- [x] GoogleTest integration
- [x] GitHub Actions CI (initial infrastructure verified by author)
- [x] Board representation and position state
- [x] FEN parsing, validation, and serialization
- [ ] Pseudo-legal and legal move generation
- [ ] Special moves: castling, en passant, and promotion
- [ ] Make/unmake with full position-state restoration
- [ ] Perft validation against reference positions and node counts
- [ ] Search and UCI protocol
- [ ] Web application and game analysis

## Progress

### Position System

- [x] Created `Position` class
- [x] Added 64-square mailbox board representation (`a1 = 0`, `h8 = 63`)
- [x] Added piece encoding
- [x] Added side-to-move state
- [x] Added castling rights
- [x] Added en-passant target square
- [x] Added halfmove and fullmove counters
- [x] Added position reset functionality
- [x] Added board and state accessors
- [x] Added validation for invalid setter inputs

### FEN

- [x] Parse board placement
- [x] Parse side to move
- [x] Parse castling rights
- [x] Parse en-passant target square
- [x] Parse halfmove clock
- [x] Parse fullmove number
- [x] Validate invalid piece characters and malformed board ranks
- [x] Validate invalid side-to-move field
- [x] Validate castling rights and king/rook placement
- [x] Validate en-passant square and pawn placement
- [x] Validate move counters
- [x] Reject extra FEN fields
- [x] Validate king counts and pawn placement on terminal ranks
- [x] Preserve the previous position when FEN loading fails
- [x] Serialize FEN and test round trips

### Build and Testing

- [x] CMake build configured
- [x] GoogleTest integrated
- [x] CTest configured
- [x] Initial test infrastructure verified
- [x] 81/81 tests passing locally (latest author-reported result)

## Next Milestone: Legal Move Generation and Perft

The next engine milestone is implementing pseudo-legal and legal move generation, followed by special moves, make/unmake, and perft validation.

Correctness will be established using reference perft positions and node counts before moving on to search optimization.

For the full project objectives, roadmap, scope, and architectural decisions, see [PROJECT_VISION.md](PROJECT_VISION.md).