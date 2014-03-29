#ifndef TIMERH
#define TIMERH


#include <time.h>
#include <stdio.h>


class Timer
{
private:

	clock_t start;
	clock_t stop;

public:
	Timer(void);

	void begin(void);
	double end(void);
};



#endif
