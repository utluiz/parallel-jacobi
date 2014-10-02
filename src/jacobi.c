#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "timer.h"
#include "results.h"
#include "jacobi.h"

/*
 * Accept as parameter:
 *  - input file
 *  - # of threads
 *  - algorithm
 *    - 0: serial
 *    - 1: pthread parallel
 *    - 2: MPI parallel
 *    - 3: OpenMP parallel
 *
 * 1. Read matrix from file
 * 2. Solve linear system through jacobi method
 * 3. Write output
 *
 * Output
 * 	Result: success or failure
 * 	Elapsed time
 */

int main(int argc, char *argv[]) {
	puts("---BEGIN---");

	if ( argc != 4 ) {
		puts("Inform input file and number of threads!");
		exit(1);
	}

	//# of threads
	int thread_count = strtol(argv[2], NULL, 4);

	//algorithm
	int algorithm = strtol(argv[3], NULL, 0);

	//prints info
	printf("Input file: '%s', thread count: %i, algorithm: %i\n\n", argv[1], thread_count, algorithm);

	//loads matrix
	matrix *m = matrix_load(argv[1]);

	//prints matrix
	matrix_print(m);

	//starts timer
	timer* t = start_timer();

	jacobi_result* result;

	switch (algorithm) {
		case 1: // pthread parallel
			break;
		case 2: // MPI parallel
			break;
		case 3: // OpenMP parallel
			break;
		case 0: // serial
		default:
			result = jacobi_serial(m);
	}

	//stops timer
	stop_timer_print(t);

	//prints result
	int i;
	for (i = 0; i < m->size; i++) {
		printf("%f, ", result->x[i]);
	}

	//saves results
	write_results(t, argv[1], thread_count, algorithm, m->size);

	//frees matrix
	matrix_destroy(m);

	//frees timer
	free(t);

	//frees result
	free(result);

	puts("\n\n---END---");
	return EXIT_SUCCESS;
}
