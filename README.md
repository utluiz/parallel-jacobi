Parallel Jacobi
===============

Parallel and serial implementations of Jacobi method for solving systems of linear equations.

This project aims to compare different versions os the algorithm with different number of variables, cores, and threads.

How they scale? How about the speed up and efficiency?

Currently there are :

- Serial version
- Parallel version with pthread: creates and detroys on each iteration
- Improved version with pthread: uses mutex and wait condition in order to syncrhonize threads