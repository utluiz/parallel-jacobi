#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "matrix.h"
#include "jacobi.h"

typedef struct {
	matrix *m;
	double *x0, *x, *x2;
	int number, initial_line, end_line;
} thread_argument_pthread;

void *jacobi_pthread_task(void *argument) {
	thread_argument_pthread *thread_arg = (thread_argument_pthread *) argument;

	matrix *m = thread_arg->m;
	double *x0 = thread_arg->x0, *x = thread_arg->x, *x2 = thread_arg->x2;
	int i, j;
	double soma;

	for (i = thread_arg->initial_line; i <= thread_arg->end_line; i++) {
		soma = 0;
		for (j = 0; j < m->size; j++) {
			//printf("Hello from thread %i\n", thread_arg->number);
			if (j != i) {
				soma += m->a[i][j] * x0[j];
			}
			//Sleep(100);
		}
		x[i] = (m->b[i] - soma) / m->a[i][i];
		x2[i] = x[i] - x0[i];
	}
   return NULL;
}

jacobi_result* jacobi_parallel_pthread(matrix *m, int thread_count, bool verbose) {

	pthread_t *threads = malloc(m->size * sizeof(pthread_t));
	thread_argument_pthread *thread_args = malloc(m->size * sizeof(thread_argument_pthread));

	int t, i, k = 0;
	double norma, norma_ant = 0, n1, n2;

	//initialize temp arrays
	double *x = malloc(m->size * sizeof(double));
	double *x0 = malloc(m->size * sizeof(double));
	double *x2 = malloc(m->size * sizeof(double));

	//initial position
	for (i = 0; i < m->size; i++) {
		x0[i] = 1;
	}

	if (thread_count > m->size) {
		thread_count = m->size;
	}
	/*
	 * Example:
	 * T  S  R
	 * 4  4  0  1 1 1 1
	 * 4  3  3  1 1 1 0
	 * 4  5  1  2 1 1 1
	 * 4  6  2  2 2 1 1
	 */
	int resto = m->size % thread_count;
	int qtd = ceil((double) m->size / thread_count);
	int initial = 0;
	for (t = 0; t < thread_count; t++) {
		thread_args[t].initial_line = initial;
		thread_args[t].end_line = initial + qtd  -1;
		//printf("%i, %i\n", thread_args[t].initial_line, thread_args[t].end_line);
		thread_args[t].number = t;
		thread_args[t].m = m;
		thread_args[t].x = x;
		thread_args[t].x0 = x0;
		thread_args[t].x2 = x2;
		initial += qtd;
		if (t == resto - 1) qtd--;
	}

	//main loop
	while (k < 100) {

		//sum up items
		for (t = 0; t < thread_count; t++) {
			pthread_create(
					&threads[t],
					NULL,
					jacobi_pthread_task,
					(void *) &thread_args[t]);
		}

		//join threads
		for (t = 0; t < thread_count; t++) {
			pthread_join(threads[t], NULL);
		}

		//calculate current error as "norma"
		n1 = 0;
		n2 = 0;
		for (i = 0; i < m->size; i++) {
			//printf("%.6f, ", x[i]);
			n1 += x2[i] * x2[i];
			n2 += x[i] * x[i];
		}
		norma = sqrt(n1 / n2);
		if (verbose) printf("\nk = %i, norma = %.20f, norma_ant = %.6f, n1 = %.6f, n2 = %.6f \n", k, norma, norma_ant, n1, n2);
		//printf("\nnorma = %.6f, norma_ant = %.6f, n1 = %.6f, n2 = %.6f \n", norma, norma_ant, n1, n2);

		if ((k > 1 && (norma <= precision)) || isnan(norma)) {
			break;
		} else {
			norma_ant = norma;
			for (i = 0; i < m->size; i++) {
				x0[i] = x[i];
			}
			k++;
		}

	}

	//prepare results
	jacobi_result* res = malloc(sizeof(jacobi_result));
	res->x = malloc(m->size * sizeof(double));
	for (i = 0; i < m->size; i++) {
		res->x[i] = x[i];
	}
	res->e = norma;
	res->k = k;

	//free memory
	free(x);
	free(x0);
	free(x2);
	free(thread_args);

	return res;
}
