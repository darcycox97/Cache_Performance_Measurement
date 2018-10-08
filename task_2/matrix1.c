/* do not add other includes */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>


double getTime(){
  struct timeval t;
  double sec, msec;
  
  while (gettimeofday(&t, NULL) != 0);
  sec = t.tv_sec;
  msec = t.tv_usec;
  
  sec = sec + msec/1000000.0;
  
  return sec;
}


int main (int argc, char *argv[])
{
  	double t1, t2; 

	/* Declare variables */
	int N = 1000;
	unsigned int i;
	unsigned int j;

	// we will compute A * B and store it in C
	double **A;
	double **B;
	double **C;

	printf("Hope i can get past here hehe\n");

	/* Allocate memory for the matrices */
	A = malloc(N * sizeof(double *));
	B = malloc(N * sizeof(double *));
	C = malloc(N * sizeof(double *));
    for (i=0; i<N; i++)
	{
 		A[i] = malloc(N * sizeof(double));
		B[i] = malloc(N * sizeof(double));
		C[i] = malloc(N * sizeof(double));
	} 

	printf("hello\n");

	/* zero the operand matrices */
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			A[i][j] = 0;
			B[i][j] = 0;
		}
	}

 
	 
	t1 = getTime();
  	/* code to be measured goes here */
  	/***************************************/
	
	// compute A * B and store it in C
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			
		}
	}
	
	
	
  	/***************************************/
	t2 = getTime(); 
  
  	/* output; examples, adjust for task */
  	printf("time: %6.2f secs\n",(t2 - t1));

  /* IMPORTANT: also print the result of the code, e.g. the sum, 
   * otherwise compiler might optimise away the code */
  
  /* free memory; examples, adjust for task */
  //free(a);

  return 0;  
}
