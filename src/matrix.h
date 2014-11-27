#ifndef MATRIX_H_
#define MATRIX_H_

typedef struct item_matrix_t {
	double value;
	int column;
} item_matrix;

typedef struct matrix_t {
	item_matrix **a;
	double *b, *x;
	unsigned int size;
} matrix;

void matrix_print(matrix *m);
matrix* matrix_load(char* filename);
void matrix_destroy(matrix* m);

#endif
