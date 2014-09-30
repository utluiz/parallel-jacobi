#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include "results.h"

void write_results(timer* t, char* inputfile, int thread_count, int size) {
	//clock time
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    long timestamp = floor(spec.tv_sec * 1.0e8 + spec.tv_nsec / 100.0);

    //date and time as string
	time_t rawtime;
	time(&rawtime);
	struct tm * timeinfo = localtime (&rawtime);
	char datetime[80];
	strftime(datetime, 80, "%F %T", timeinfo);

   	//write to file
   	FILE* f = fopen("results.txt", "a");
	fprintf(f, "%s\t%s\t%li\t%i\t%i\t%.9f\t%.9f\t%i\t%.9f\t\n",
			inputfile,
			datetime,
			timestamp,
			thread_count,
			size,
			t->timeval_diff,
			t->timespec_diff,
			(int) t->clock_diff,
			t->clock_diff_time);
	fclose(f);
}
