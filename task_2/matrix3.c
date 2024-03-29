/* do not add other includes */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

// Darcy Cox, dcox740

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

int main(int argc, char *argv[])
{
  double t1, t2;

  /* Declare variables */
  int N = 1000;
  unsigned int i;
  unsigned int j;
  unsigned int k;
  unsigned int blockSize; // block size is blockSize x blockSize
  unsigned int rowOffset;
  unsigned int colOffset;
  double sum;

  // we will compute A * B and store it in C
  double **A;
  double **B;
  double **C;

  /* Allocate memory for the matrices */
  A = malloc(N * sizeof(double *));
  B = malloc(N * sizeof(double *));
  C = malloc(N * sizeof(double *));
  for (i = 0; i < N; i++)
  {
    A[i] = malloc(N * sizeof(double));
    B[i] = malloc(N * sizeof(double));
    C[i] = malloc(N * sizeof(double));
  }

  /* zero the matrices */
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {

      A[i][j] = 0;
      B[i][j] = 0;
      C[i][j] = 0;
    }
  }

  /* Put some values into the operand matrices so we know the multiplication is correct. 
	 * With the values, C[0][0] = 26, C[0][1] = 46, C[1][0] = 22, C[1][1] = 39 */
	A[0][0] = 1;
	A[0][1] = 2;
	A[0][2] = 3;
	A[0][3] = 4;
	A[1][0] = 2;
	A[1][1] = 1;
	A[1][2] = 2;
	A[1][3] = 3;

	B[0][0] = 3;
	B[0][1] = 5;
	B[1][0] = 2;
	B[1][1] = 1;
	B[2][0] = 1;
	B[2][1] = 5;
	B[3][0] = 4;
	B[3][1] = 6;

  t1 = getTime();
  /* code to be measured goes here */
  /***************************************/

  // compute A * B using blocking and store it in C
  // A is partitioned into slivers of length blockSize, and B is partitioned into blocks of blockSize x blockSize. 
  // For each blockSize x blockSize block of B, N 1 x blockSize slivers are accessed. The sum of each entry in C
  // is accumulated over several blocks before the entry is fully computed.
  blockSize = 64; // (block of B) 64 x 64 x 8 + (sliver of A) 64 x 8 < L1CacheSize so we are minimizing cache misses
  for (rowOffset = 0; rowOffset < N; rowOffset += blockSize)
  {
    for (colOffset = 0; colOffset < N; colOffset += blockSize)
    {
      // for each block, calculate the part of each entry in C
      // that we possibly can while only using the blockSize x blockSize block
      for (i = 0; i < N; i++)
      { 
        for (j = colOffset; j < colOffset + blockSize && j < N; j++)
        {
          // adding onto the previously accumulated value for this particular C entry
          sum = C[i][j];
          for (k = rowOffset; k < rowOffset + blockSize && k < N; k++)
          {
            sum += A[i][k] * B[k][j];
          }
          // further accumulate the value for this entry
          C[i][j] = sum;
        }
      }
    }
  }
  /***************************************/
  t2 = getTime();

  printf("time: %6.2f secs\n", (t2 - t1));
  printf("C[0][0]: %.1lf\n", C[0][0]);
	printf("C[0][1]: %.1lf\n", C[0][1]);
	printf("C[1][0]: %.1lf\n", C[1][0]);
	printf("C[1][1]: %.1lf\n", C[1][1]);
  
  /* Free memory allocated to arrays */
  for (i = 0; i < N; i++)
  {
    free(A[i]);
    free(B[i]);
    free(C[i]);
  }

  free(A);
  free(B);
  free(C);

  return 0;
}
