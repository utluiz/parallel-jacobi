#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matrix.h"
#include "jacobi.h"

jacobi_result* jacobi_serial(matrix *m, bool verbose) {
	int i, j, k = 0;
	double norma, norma_ant = 0, soma, n1, n2;

	//initialize temp arrays
	double *x = malloc(m->size * sizeof(double));
	double *x0 = malloc(m->size * sizeof(double));
	//double *x2 = malloc(m->size * sizeof(double));
	double x2;

	//initial position
	for (i = 0; i < m->size; i++) {
		x0[i] = 1;
	}

	//main loop
	while (k < 100) {

		n1 = 0;
		n2 = 0;
		for (i = 0; i < m->size; i++) {
			//sum up line items
			soma = 0;
			item_matrix *item = m->a[i];
			if (item) {
				double diagonal_value = 0;
				while (item->column >= 0) {
					j = item->column;
					if (j >= m->size) {
						puts("opa");
						exit(0);
					}
					if (j != i) {
						soma += item->value * x0[j];
					} else {
						diagonal_value = item->value;
					}
					item++;
				}
				x[i] = (m->b[i] - soma) / diagonal_value;
				x2 = x[i] - x0[i];

				n1 += x2 * x2;
				n2 += x[i] * x[i];
			}
		}

		//calculate current error as "norma"
		norma = sqrt(n1 / n2);
		if (verbose) printf("\nk = %i, norma = %.20f, norma_ant = %.6f, n1 = %.6f, n2 = %.6f \n", k, norma, norma_ant, n1, n2);

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
	//free(x2);

	return res;
}
