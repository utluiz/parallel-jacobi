#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <windows.h>
#include "matrix.h"
#include "jacobi.h"


typedef struct {
	matrix *m;
	double *x0, *x;
	int number, lines_to_process;
} thread_argument_pthread;

void *jacobi_pthread_task(void *argument)
{
	thread_argument_pthread *thread_arg = (thread_argument_pthread *) argument;

	matrix *m = thread_arg->m;
	double *x0 = thread_arg->x0, *x = thread_arg->x;
	int j, soma = 0, i = thread_arg->number;
	for (j = 0; j < m->size; j++) {
		//printf("Hello from thread %i\n", thread_arg->number);
		if (j != i) {
			soma += m->a[i][j] * x0[j];
		}
		//Sleep(100);
	}
	x[i] = (m->b[i] - soma) / m->a[i][i];

   return NULL;
}

jacobi_result* jacobi_parallel_pthread(matrix *m, int thread_count) {

	pthread_t *threads = malloc(m->size * sizeof(pthread_t));
	thread_argument_pthread *thread_args = malloc(m->size * sizeof(thread_argument_pthread));

	int i, k = 0;
	double norma, norma_ant = 0, n1, n2;

	//initialize temp arrays
	double *x = malloc(m->size * sizeof(double));
	double *x0 = malloc(m->size * sizeof(double));
	double *x2 = malloc(m->size * sizeof(double));

	//initial position
	for (i = 0; i < m->size; i++) {
		x0[i] = 1;
	}

	//main loop
	while (k < 100) {

		//TODO fork by thread_count
		//sum up items
		for (i = 0; i < m->size; i++) {
			thread_args[i].lines_to_process = 1;
			thread_args[i].number = i;
			thread_args[i].m = m;
			thread_args[i].x = x;
			thread_args[i].x0 = x0;
			pthread_create(
					&threads[i],
					NULL,
					jacobi_pthread_task,
					(void *) &thread_args[i]);
		}

		//join threads
		for (i = 0; i < m->size; i++) {
			pthread_join(threads[i], NULL);
		}

		//calculate current error as "norma"
		n1 = 0;
		n2 = 0;
		for (i = 0; i < m->size; i++) {
			printf("%f.6, ", x[i]);
			x2[i] = x[i] - x0[i];
			n1 += x2[i] * x2[i];
			n2 += x[i] * x[i];
		}
		norma = sqrt(n1 / n2);
		printf("\nnorma = %.6f, norma_ant = %.6f, n1 = %.6f, n2 = %.6f \n", norma, norma_ant, n1, n2);

		if (k > 1 && (norma <= precision)) {
			break;
		} else {
			norma_ant = norma;
			for (i = 0; i < m->size; i++) {
				x0[i] = x[i];
			}
			k++;
		}

	}


	printf("In main: All threads completed successfully\n");

	//prepare results
	jacobi_result* res = malloc(sizeof(jacobi_result));
	res->x = malloc(m->size * sizeof(double));
	for (i = 0; i < m->size; i++) {
		res->x[i] = x[i];
	}
	res->e = norma - norma_ant;
	res->k = k;

	//free memory
	free(x);
	free(x0);
	free(x2);

	return res;
}
