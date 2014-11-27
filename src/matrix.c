#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "matrix.h"

/**
 * http://math.nist.gov/MatrixMarket/formats.html
 *
 * It's necessary to remove headers
 */
matrix* matrix_load_mm(char* filename) {

	long i, size, size_cols, count, row, col;

	//open file
	FILE *file;
	file = fopen(filename, "r");
	if (file == NULL) {
		puts("\nCannot open file");
		puts(filename);
		exit(1);
	}

	//read matrix size
	fscanf(file, "%li", &size);
	fscanf(file, "%li", &size_cols);
	fscanf(file, "%li", &count);

	if (size != size_cols) {
		puts("\nMatrix not symmetric");
		exit(1);
	}

	//creates matrix
	matrix *m = malloc(sizeof(matrix));
	m->size = size;

	//allocates vector right "B"
	m->b = malloc(size * sizeof(double));

	//allocates vector with expected results
	m->x = malloc(size * sizeof(double));

	//allocates "rows"
	m->a = malloc(size * sizeof(item_matrix*));
	for (i = 1;i < size; i++) {
		m->a[i] = NULL;
	}

	//allocates matrix contents
	m->a[0] = malloc((count + size) * sizeof(item_matrix));

	//read matrix A
	item_matrix *position = m->a[0];
	int last_row = 1;
	for (i = 0; i < count; i++) {
		fscanf(file, "%li", &row);
		fscanf(file, "%li", &col);
		if (row != last_row) {
			position->column = -1;
			position++;
		}
		position->column = col - 1;
		if (!fscanf(file, "%lf", &position->value)) {
			break;
		}
		if (row != last_row) {
			m->a[row - 1] = position;
			last_row = row;
		}
		position++;

	}
	position->column = -1;

	//read vector B
	char filename_b[100];
	strncpy((char*)  &filename_b, filename, strlen(filename) - 4);
	filename_b[strlen(filename) - 4] = '\0';
	strcat((char*) &filename_b, "_b.mtx");
	file = fopen(filename_b, "r");
	if (file == NULL) {
		puts("\nCannot open file");
		puts(filename_b);
		exit(1);
	}

	//ignores
	fscanf(file, "%li", &count);
	fscanf(file, "%li", &size_cols);

	for (i = 0; i < count; i++) {
		if (!fscanf(file, "%lf", &m->b[i])) {
			break;
		}
	}

	fclose(file);

	//read expected results from vector X
	char filename_x[100];
	strncpy((char*) &filename_x, filename, strlen(filename) - 4);
	filename_x[strlen(filename) - 4] = '\0';
	strcat((char*) &filename_x, "_x.mtx");

	if (access(filename_x, R_OK) != -1) {

		file = fopen(filename_x, "r");
		if (file == NULL) {
			puts("\nCannot open file");
			puts(filename_x);
			exit(1);
		}

		//ignores
		fscanf(file, "%li", &count);
		fscanf(file, "%li", &size_cols);

		for (i = 0; i < count; i++) {
			if (!fscanf(file, "%lf", &m->x[i])) {
				break;
			}
		}

		fclose(file);
	} else {
		for (i = 0; i < size; i++) {
			m->x[i] = -1.0;
		}
	}

	return m;

}

matrix* matrix_load_original(char* filename) {
	int i, j, size;
	matrix *m = malloc(sizeof(matrix));

	//open file
	FILE *file;
	file = fopen(filename, "r");
	if (file == NULL) {
		puts("\nCannot open file");
		puts(filename);
		exit(1);
	}

	//read matrix size
	fscanf(file, "%iu", &size);

	//allocates vector right "B"
	m->b = malloc(size * sizeof(double));

	//allocates vector with expected results
	m->x = malloc(size * sizeof(double));

	//allocates "rows"
	m->a = malloc(size * sizeof(item_matrix*));

	//allocates matrix contents
	m->a[0] = malloc((size*size + size) * sizeof(item_matrix));

	char c[10];

	//read rows
	item_matrix *position = m->a[0];
	for (i = 0; i < size; i++) {
		m->a[i] = position;
		//read cols
		for (j = 0; j < size; j++) {
			position->column = j;
			if (!fscanf(file, "%lf", &position->value)) {
				break;
			}
			position++;
		}
		position->column = -1;
		position++;

		fscanf(file, "%s", (char*) &c);

		if (!fscanf(file, "%lf", &m->b[i])) {
			break;
		}
	}

	//read expected results
	for (i = 0; i < size; i++) {
		if (!fscanf(file, "%lf", &m->x[i])) {
			break;
		}
	}
	fclose(file);

	m->size = size;
	return m;
}


bool is_mm(char* filename) {
	char *dot = strrchr(filename, '.');
	return dot && !strcmp(dot, ".mtx");
}

matrix* matrix_load(char* filename) {
	if (is_mm(filename)) {
		return matrix_load_mm(filename);
	}
	return matrix_load_original(filename);
}


void matrix_destroy(matrix* matrix) {
	#ifndef __linux__
		return;
	#endif
	//int i;
	//for (i = 0; i < matrix->size; i++) {
		//free(matrix->a[i]);
	//}
	//free(matrix->a);
	//free(matrix->b);
	//free(matrix->x);
	free(matrix);
}

void matrix_print(matrix *m) {
	int i, j = 0, s = m->size;
	puts("aqui");
	for (i = 0; i < s && i < 200; i++) {
		item_matrix *item = m->a[i];
		if (item) {
			while (item->column >= 0 && j < 200) {
				j = item->column;
				printf("(%i,%i)=%f ", i, j, item->value);
				item++;
			}
		}
		printf("= %f\n", m->b[i]);
	}
	for (i = 0; i < s && i < 200; i++) {
		if (i > 0) printf(", ");
		printf("%f", m->x[i]);
	}
	puts("\n");
}
