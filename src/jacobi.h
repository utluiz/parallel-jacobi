#include "matrix.h"

#ifndef JACOBI_SERIAL_H_
#define JACOBI_SERIAL_H_

#define precision 0.01

typedef struct jacobi_result_t {
	double* x;
	int k;
	double e;
} jacobi_result;

jacobi_result* jacobi_serial(matrix *m);

#endif /* JACOBI_SERIAL_H_ */
