# Conway's Game of Life - C++ Implementation

This is a C++ implementation of Conway's Game of Life, a cellular automaton devised by John Conway. The project allows users to simulate the game on a customizable grid, with support for two different internal representations of the grid:

- **Circular matrix using vectors** (`CircularMatrix.h`)
- **Circular matrix using a map** (`CircularMatrix_map.h`)

## Features

- Customizable grid size: Users can specify the width and height of the grid at runtime.
- Customizable update time (in seconds): Users can set the time between states updates.
- Two interchangeable internal grid implementations.
- Simple mechanism to switch between vector-based and map-based grid implementations by modifying the included header file.

## Grid Implementations

### 1. Circular Matrix Using Vectors
This implementation represents the grid as a vector of vectors, allowing for constant-time access to grid cells using direct indexing. The grid behaves in a circular manner, meaning the borders wrap around, giving the effect of an infinite plane.

- **Time Complexity**: O(1) access and modification of each cell.
- **Space Complexity**: O(n × m), where n is the number of rows (height) and m is the number of columns (width).

### 2. Circular Matrix Using Maps
This implementation uses a map (associative container) to store the grid, with each cell being represented as a key-value pair. This is particularly useful for sparse grids where the majority of cells are dead, as it saves space by only storing active cells.

- **Time Complexity**: O(log n) access and modification of each cell (due to map operations).
- **Space Complexity**: O(k), where k is the number of alive cells, making it more space-efficient for sparse matrices.

## Switching Between Implementations

The grid implementation is generic and modular. To switch between the vector-based and map-based grid, simply change the included header file in your project:

- For **vector-based** implementation, include in Grid.h:
  #include "CircularMatrix.h"

- For **map-based** implementation, include in Grid.h:
  #include "CircularMatrix_map.h"
