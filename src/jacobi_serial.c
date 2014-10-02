#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matrix.h"
#include "jacobi.h"

jacobi_result* jacobi_serial(matrix *m) {
	int i, j, k = 0;
	double norma, norma_ant = 0, soma, n1, n2;

	//initialize temp arrays
	double *x = malloc(m->size * sizeof(double));
	double *x0 = malloc(m->size * sizeof(double));
	double *x2 = malloc(m->size * sizeof(double));

	//initial position
	for (i = 0; i < m->size; i++) {
		x0[i] = 1;
	}

	//main loop
	while (k < 1000) {

		//sum up items
		soma = 0;
		for (i = 0; i < m->size; i++) {
			for (j = 0; j < m->size; j++) {
				if (j != i) {
					soma += m->a[i][j] * x0[j];
				}
			}
			x[i] = (m->b[i] - soma) / m->a[i][i];
		}

		//calculate current error as "norma"
		n1 = 0;
		n2 = 0;
		for (i = 0; i < m->size; i++) {
			x2[i] = x[i] - x0[i];
			n1 += x2[i] * x2[i];
			n2 += x[i] * x[i];
		}
		norma = sqrt(n1 / n2);
		printf("norma = %f, norma_ant = %f, n1 = %f, n2 = %f \n",
				norma, norma_ant, n1, n2);

		if (k > 1 && norma <= precision) {
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
	res->e = norma - norma_ant;
	res->k = k;

	//free memory
	free(x);
	free(x0);
	free(x2);

	return res;
}
