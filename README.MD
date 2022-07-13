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