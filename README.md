# Game of Life

This C++ program displays [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) with a randomly generated first generation. The user can specify the number of rows of the grid, the resolution of the window and speed of the animation. At the moment, this program can only run on Linux.

## Installation

Make sure a C++ compiler, [CMake](https://cmake.org/) and [GLFW](https://www.glfw.org/) are installed on your machine. On Debian, one could use these commands:

- `sudo apt install build-essential`
- `sudo apt install cmake`
- `sudo apt install libglfw3-dev`


## Usage

After having built the application, you can use the following flags:

- `--rows` number of rows of the grid (default 64)
- `--resolution` resolution of window in WIDTHxHEIGHT format, make sure there are no spaces between the numbers and the `x` (default 640x480)
- `--speed` number of seconds between generations (default 0.1)
