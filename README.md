# Mandelbrot Set Visualization

This project generates and visualizes the Mandelbrot set using C, C++, and CUDA. The Mandelbrot set is a famous fractal that is generated by iterating a simple mathematical formula.Compares the performance of the three implementations and demonstrates the benefits of parallel processing using CUDA.

## Prerequisites

- GCC (for compiling C code)
- G++ (for compiling C++ code)
- NVCC (for compiling CUDA code)
- Make (for building the project)
- CUDA Toolkit (for running CUDA code)

## Installation

1. Clone the repository:

   ```sh
   git clone https://https://github.com/Pp3ng/Mandelbrot-Set.git
   cd Mandelbrot-Set
   ```

2. Ensure you have the required compilers and tools installed:
   ```sh
   sudo apt install nvidia-cuda-toolkit
   ```

## Usage

1. Build the project using Make:

   ```sh
   make
   ```

   Only compile three implementations.

2. Run the generated executables:

   ```sh
   make run
   ```

   Run the C, C++ and CUDA implementations and compare their performance.

3. Clean the build files:
   ```sh
   make clean
   ```

## Comparison of Models

### C Implementation

- **Description**: A basic implementation using C.
- **Performance**: Suitable for small datasets, but slower for larger datasets due to lack of parallelism.
- **Usage**: Simple and straightforward, ideal for understanding the basic algorithm.

### C++ Implementation

- **Description**: An enhanced version using C++ with multithreading.
- **Performance**: Faster than the C implementation due to parallel processing.
- **Usage**: Requires understanding of multithreading concepts.

### CUDA Implementation

- **Description**: A high-performance version using CUDA for GPU acceleration.
- **Performance**: Significantly faster, especially for large datasets, due to massive parallelism.
- **Usage**: Requires a compatible NVIDIA GPU and understanding of CUDA programming.
