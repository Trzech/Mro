#include "Timer.h"

Timer::Timer() {

}

void Timer::begin(void) {
	start = clock();
}

double Timer::end(void) {
	stop = clock();
	double result = (double) (stop - start) / CLOCKS_PER_SEC;
	printf("Time: %f\n", result);
	return result;
}

