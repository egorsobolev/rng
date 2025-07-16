#include "rng.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

#ifndef N
#define N 10000
#endif
#ifndef M
#define M 100
#endif

int main()
{
  double x[N];
  int i, j;
  unsigned int seed;
  struct timeval tm;
  pid_t pid;

  pid = getpid();
  gettimeofday(&tm, NULL);
  seed = (int) tm.tv_usec * (int) pid;

  rng_init(seed);

  for (j = 0; j < 1000; j++) {
    rng_gaussian_d(N,x,1);
    for (i =0 ; i< N; i++)
      printf("%.16e\n", x[i]);
  }

  exit(EXIT_SUCCESS);
}
