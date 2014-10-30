Parallel Jacobi
===============

Parallel and serial implementations of **Jacobi Method** for solving systems of linear equations.

This project aims to compare serial and parallel implementations of the algorithm with different number of variables, cores, and threads.

How they scale? How about the speed up and efficiency?

Currently there are implemented:

- Serial version
- Parallel with pthread: creates and detroys threads on each iteration
- Improved pthread version: uses mutex and wait condition in order to syncrhonize and reuse threads
- OpenMP version

## TO DO

- MPI version