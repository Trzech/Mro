#if !defined(DEF_TTIMING)
#define DEF_TTIMING


#include <time.h>


class TTiming
{
protected:

	clock_t start;
	clock_t stop;



public:
	TTiming(void);

	void Begin(void);
	double End(void);
};

inline TTiming::TTiming(void)
{

}

inline void TTiming::Begin(void)
{
	start = clock();
}

inline double TTiming::End(void)
{
	stop = clock();

		double result1  = (double)(stop - start)/CLOCKS_PER_SEC;

		printf("clock(): %f\n", result1);



		return result1;
}

#endif
