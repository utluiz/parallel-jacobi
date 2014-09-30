#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "timer.h"
#include "results.h"

/*
 * Accept as parameter:
 *  # input file
 *  # of threads
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

	 if ( argc != 3 ) {
		 puts("Inform input file and number of threads!");
		 exit(1);
	 }

	//# of threads
	int thread_count = strtol(argv[2], NULL, 10);

	//prints info
	printf("Reading file '%s', thread count: %i\n\n", argv[1], thread_count);

	//loads matrix
	matrix *m = matrix_load(argv[1]);

	//starts timer
	timer* t = start_timer();

	//prints amtrix
	matrix_print(m);

	//TODO implement jacobi here

	//stops timer
	stop_timer_print(t);

	//saves results
	write_results(t, argv[1], thread_count, m->size);

	//frees matrix
	matrix_destroy(m);

	//frees timer
	free(t);

	puts("\n\n---END---");
	return EXIT_SUCCESS;
}
