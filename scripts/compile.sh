#!/bin/sh

#gcc -fopenmp -O3 -W -Wall -o jacobi \
gcc -fopenmp -O3 -o jacobi \
	../src/jacobi_parallel_omp.c \
	../src/jacobi_parallel_pthread_better.c \
	../src/jacobi_parallel_pthread.c \
	../src/jacobi_serial.c \
	../src/jacobi.c \
	../src/matrix.c \
	../src/results.c \
	../src/timer.c \
	-lm -lpthread
