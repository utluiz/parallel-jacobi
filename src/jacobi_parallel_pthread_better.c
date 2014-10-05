#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
//#include <windows.h>
#include "matrix.h"
#include "jacobi.h"

typedef struct {
	matrix *m;
	double *x0, *x, *x2;
	int number, initial_line, end_line;
} thread_argument_pthread_better;

//thread sync
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t count_threshold_cv = PTHREAD_COND_INITIALIZER;
pthread_cond_t count_threshold_global = PTHREAD_COND_INITIALIZER;
bool fim = false;
int thread_finished = 0;
int thread_count_global = 0;

void *jacobi_pthread_task_better(void *argument)
{
	thread_argument_pthread_better *thread_arg =
			(thread_argument_pthread_better *) argument;

	matrix *m = thread_arg->m;
	double *x0 = thread_arg->x0, *x = thread_arg->x, *x2 = thread_arg->x2;
	int i, j;
	double soma;

	//loop while not converge
	while (!fim) {

		//printf("Hello from thread %i\n", thread_arg->number);
		for (i = thread_arg->initial_line; i <= thread_arg->end_line; i++) {
			soma = 0;
			for (j = 0; j < m->size; j++) {
				if (j != i) {
					soma += m->a[i][j] * x0[j];
				}
				//Sleep(100);
			}
			x[i] = (m->b[i] - soma) / m->a[i][i];
			x2[i] = x[i] - x0[i];
		}

		//wait until another task or finish
		pthread_mutex_lock(&count_mutex);
		thread_finished++;
		//printf("Finished thread %i\n", thread_arg->number);
        if (thread_finished == thread_count_global) {
    		//printf("releasing global main %i\n", thread_arg->number);
        	pthread_cond_signal(&count_threshold_global);
        }
		pthread_cond_wait(&count_threshold_cv, &count_mutex);
       	pthread_mutex_unlock(&count_mutex);

	}

	return NULL;
}

jacobi_result* jacobi_parallel_pthread_better(matrix *m, int thread_count) {

	pthread_t *threads = malloc(m->size * sizeof(pthread_t));
	thread_argument_pthread_better *thread_args =
			malloc(m->size * sizeof(thread_argument_pthread_better));

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
	thread_count_global = thread_count;
	thread_finished = 0;

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

	//create threads
	//puts("starting threads");
	for (t = 0; t < thread_count; t++) {
		pthread_create(
				&threads[t],
				NULL,
				jacobi_pthread_task_better,
				(void *) &thread_args[t]);
	}

	//main loop
	while (k < 100) {

		//wait all threads
		pthread_mutex_lock(&count_mutex);
		while (thread_finished < thread_count) {
			//printf("finished until now: %i", thread_finished);
			//puts("waiting threads");
			pthread_cond_wait(&count_threshold_global, &count_mutex);
		}
		//printf("finished until now: %i", thread_finished);
		pthread_mutex_unlock(&count_mutex);
		//puts("finished threads");

		//calculate current error as "norma"
		n1 = 0;
		n2 = 0;
		for (i = 0; i < m->size; i++) {
			//printf("%.6f, ", x[i]);
			n1 += x2[i] * x2[i];
			n2 += x[i] * x[i];
		}
		norma = sqrt(n1 / n2);
		//printf("\nnorma = %.6f, norma_ant = %.6f, n1 = %.6f, n2 = %.6f \n", norma, norma_ant, n1, n2);

		if (k > 1 && (norma <= precision)) {
			break;
		} else {
			norma_ant = norma;
			for (i = 0; i < m->size; i++) {
				x0[i] = x[i];
			}
			k++;
			thread_finished = 0;

			//sum up rows
			//puts("releasing threads");
			pthread_cond_broadcast(&count_threshold_cv);

		}

	}

	//join threads
	//puts("fim = true");
	fim = true;
	pthread_cond_broadcast(&count_threshold_cv);

	for (t = 0; t < thread_count; t++) {
		pthread_join(threads[t], NULL);
	}

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
	free(thread_args);

	return res;
}
