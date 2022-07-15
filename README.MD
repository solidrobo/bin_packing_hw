# Build instructions

## Requrements

To build CMake must be installed and correctly configured. For testing Python 3+ is also needed.

## How to build

Create a separate directory e.g. "build" in the root directory and run the following commands inside it:

`cmake ..`

and then

`cmake --build . --target all`

## Running tests

To run tests run the following command inside the build folder:

`ctest`

# Runing the application

The build process will produce a binary called `bin_packing`. This binary will take as an input the path to a file - optinally an additional argument `-v` for verbose mode can be specified. Up to at most 100 characters will be read from the file, while any line over 10 characters will be discarded and words with any non ASCII letter characters will also be discarded (e.g. the file should contain one word per line, max 10 characters long and in ASCII coding). 