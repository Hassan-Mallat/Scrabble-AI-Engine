# High-Performance Scrabble AI (C++)

![C++](https://img.shields.io/badge/Language-C++17-blue.svg) ![Grade](https://img.shields.io/badge/Grade-20%2F20-brightgreen.svg)

This project implements a competitive Scrabble AI engine capable of generating moves in near-constant time. It features a custom **GADDAG** data structure and an optimized **Backtracking** algorithm.

**Achievement:** Ranked **1st in Class (Major de Promotion for this project)** at Université Claude Bernard Lyon 1.

## Key Technical Features
* **Data Structure:** Directed Acyclic Word Graph (GADDAG) for bidirectional word generation.
* **Algorithm:** Depth-First Search (DFS) with pruning strategies.
* **Memory Management:** Optimized use of `std::vector` and pointer arithmetic to minimize overhead.
* **Constraints:** Full Cross-checking implementation for 2D board validity.


## Build & Run
This project includes a **Makefile** for easy compilation.
The source code is located in the `src` directory.

```bash
# 1. Enter the source directory
cd src

# 2. Build the project
make

# 3. Run the executable
./test_board

# 4. Clean build files (optional)
make clean
