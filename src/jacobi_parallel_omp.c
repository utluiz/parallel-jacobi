#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>
#include <memory.h>
#include "matrix.h"
#include "jacobi.h"


jacobi_result* jacobi_parallel_omp(matrix *m, int thread_count, bool verbose) {

	int k = 0, t, termina = 0;
	double norma = 0, norma_ant = 0, n1 = 0, n2 = 0;

	//initialize temp arrays
	int line_size = m->size * sizeof(double);
	double *x = malloc(line_size);
	double *x0 = malloc(line_size);

	//initial position
	for (t = 0; t < m->size; t++) {
		x0[t] = 1;
	}

	//main loop
	#pragma omp parallel num_threads(thread_count) \
		shared(norma, norma_ant, k, termina, n1, n2, m)
	{
		double soma, x2;
		int i, j;
		while (termina == 0 && k < 100) {

			//sum up items for each row
			//#pragma omp for reduction(+:n1, n2) private (j, soma, x2) //nowait
			//# dynamic, static, guided, runtime
			#pragma omp for reduction(+:n1, n2) private (j, soma, x2) schedule(runtime)
			for (i = 0; i < m->size; i++) {
				soma = 0;
				for (j = 0; j < m->size; j++) {
					if (j != i) {
						soma += m->a[i][j] * x0[j];
					}
				}
				x[i] = (m->b[i] - soma) / m->a[i][i];
				x2 = x[i] - x0[i];

				//reduction for norma
				n1 += x2 * x2;
				n2 += x[i] * x[i];
			}

			//synchronize all threads (already has an implicit barrier after for)
			//#pragma omp barrier

			//only main thread
			//#pragma omp master
			#pragma omp single
			{
				//calculate current error as "norma"
				norma = sqrt(n1 / n2);

				if (verbose) printf("\nk = %i, norma = %.20f, norma_ant = %.6f, n1 = %.6f, n2 = %.6f \n", k, norma, norma_ant, n1, n2);
				//printf("\nnorma = %.6f, norma_ant = %.6f, n1 = %.6f, n2 = %.6f \n", norma, norma_ant, n1, n2);

				//reset totals
				n1 = 0;
				n2 = 0;

				if ((k > 1 && (norma <= precision)) || isnan(norma)) {
					termina = 1;
				} else {
					norma_ant = norma;
					memcpy(x0, x, line_size);
					k++;
				}

			}

		} //end of while, the main loop from jacobi
	} //end of parallel block

	//preparer results
	jacobi_result* res = malloc(sizeof(jacobi_result));
	res->x = malloc(line_size);
	/*for (t = 0; t < m->size; t++) {
		res->x[t] = x[t];
	}*/
	memcpy(res->x, x, line_size);
	res->e = norma;
	res->k = k;

	//free memory
	free(x);
	free(x0);

	return res;

}
