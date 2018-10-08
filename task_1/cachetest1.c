/* do not add other includes */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

double getTime()
{
	struct timeval t;
	double sec, msec;

	while (gettimeofday(&t, NULL) != 0);
	sec = t.tv_sec;
	msec = t.tv_usec;

	sec = sec + msec / 1000000.0;

	return sec;
}

void usage(void)
{
	fprintf(stderr, "Usage: cachetest1 [--repetitions M] [--array_size N]\n");
	exit(1);
}

int main(int argc, char *argv[])
{
	double t1, t2;

	/* declare variables */
	unsigned int M = 1000;
	unsigned int N = 256 * 1024;
	unsigned int i;
	unsigned int j;

	int *a;
	int *b;
	int sum;

	/* parameter parsing task 1 */
	for (i = 1; i < (unsigned)argc; i++)
	{
		if (strcmp(argv[i], "--repetitions") == 0)
		{
			i++;
			if (i < argc)
				sscanf(argv[i], "%u", &M);
			else
				usage();
		}
		else if (strcmp(argv[i], "--array_size") == 0)
		{
			i++;
			if (i < argc)
				sscanf(argv[i], "%u", &N);
			else
				usage();
		}
		else
			usage();
	}

	/* allocate memory for arrays */
	a = malloc(N * sizeof(int));
	b = malloc(N * sizeof(int));

	/* initialise array elements */
	// array b contains possible index values for accessing array a
	// array a should be init to zero
	for (i = 0; i < N; i++)
	{
		b[i] = i;
		a[i] = 0;
	}


	t1 = getTime();

	/* code to be measured goes here */
	/***************************************/
	// repeat M times
	for (i = 0; i < M; i++)
	{
		sum = 0;
		for (j = 0; j < N; j++)
		{
			sum += a[b[j]];
		}
	}

	/***************************************/
	t2 = getTime();

	printf("time: %6.2f secs\n", (t2 - t1));

	/* IMPORTANT: also print the result of the code, e.g. the sum,
     * otherwise compiler might optimise away the code */
	printf("sum: %d\n", sum);

	/* free memory */
	free(a);
	free(b);

	return 0;
}
