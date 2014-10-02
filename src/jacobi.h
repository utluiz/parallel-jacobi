#include "matrix.h"

#ifndef JACOBI_SERIAL_H_
#define JACOBI_SERIAL_H_

#define precision 0.000001

typedef struct jacobi_result_t {
	double* x;
	int k;
	double e;
} jacobi_result;

jacobi_result* jacobi_serial(matrix *m);

jacobi_result* jacobi_parallel_pthread(matrix *m, int thread_count);

#endif /* JACOBI_SERIAL_H_ */
