#include <stdbool.h>
#include "matrix.h"

#ifndef JACOBI_SERIAL_H_
#define JACOBI_SERIAL_H_

#define precision 0.0001

typedef struct jacobi_result_t {
	double* x;
	int k;
	double e;
} jacobi_result;

jacobi_result* jacobi_serial(matrix *m, bool verbose);
jacobi_result* jacobi_parallel_pthread(matrix *m, int thread_count, bool verbose);
jacobi_result* jacobi_parallel_pthread_better(matrix *m, int thread_count, bool verbose);
jacobi_result* jacobi_parallel_omp(matrix *m, int thread_count, bool verbose);

#endif /* JACOBI_SERIAL_H_ */
