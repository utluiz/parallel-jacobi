#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "matrix.h"

matrix* matrix_load(char* filename) {
	int i, j, size;
	matrix *m = malloc(sizeof(matrix));

	//open file
	FILE *file;
	file = fopen(filename, "r");
	if (file == NULL) {
		puts("\nCannot open file\n");
		exit(1);
	}

	//read matrix size
	fscanf(file, "%iu", &size);

	//allocates "rows"
	m->a = malloc(size * sizeof(double*));

	//allocates vector right "B"
	m->b = malloc(size * sizeof(double));

	//allocates vector with expected results
	m->x = malloc(size * sizeof(double));

	//allocates "cols"
	for (i = 0;i < size; i++) {
		m->a[i] = malloc(size*sizeof(double));
	}

	char c[10];

	//read rows
	for(i = 0; i < size; i++) {
		//read cols
		for(j = 0; j < size; j++) {
			if (!fscanf(file, "%lf", &m->a[i][j])) {
				break;
			}
		}
		fscanf(file, "%s", &c);

		if (!fscanf(file, "%lf", &m->b[i])) {
			break;
		}
	}

	//read expected results
	for(i = 0; i < size; i++) {
		if (!fscanf(file, "%lf", &m->x[i])) {
			break;
		}
	}
	fclose(file);

	m->size = size;
	return m;
}

void matrix_destroy(matrix* matrix) {
	int i;
	for (i = 0; i < matrix->size; i++) {
		free(matrix->a[i]);
	}
	free(matrix->a);
	free(matrix->b);
	free(matrix->x);
	free(matrix);
}

void matrix_print(matrix *m) {
	int i, j, s;
	s = m->size;
	for (i = 0; i < s; i++) {
		for (j = 0; j < s; j++) {
			printf("%f ", m->a[i][j]);
		}
		printf("= %f\n", m->b[i]);
	}
	puts("\nExpected result: ");
	for (i = 0; i < s; i++) {
		if (i > 0) printf(", ");
		printf("%f", m->x[i]);
	}
	puts("\n");
}
