#include <time.h>
#include <sys/time.h>


#ifndef TIMER_H_
#define TIMER_H_

typedef struct timer_t {
	struct timeval timeval_start, timeval_end;
	struct timespec timespec_start, timespec_end;
	clock_t clock_start, clock_end, clock_diff;
	double timeval_diff, timespec_diff, clock_diff_time;
} timer;

timer* start_timer();
void stop_timer(timer* t);
void stop_timer_print(timer* t);

#endif
