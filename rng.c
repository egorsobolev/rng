#include "mt19937ar.h"
#include "ziggurat.h"

void rng_uniform_i(int n, int *x, unsigned int mx)
{
  int i;
  unsigned m = mx + 1;
  for (i = 0; i < n; i++)
    x[i] = (int) (genrand_real2() * m);
}

void rng_uniform_d(int n, double *x, double mx)
{
  int i;
  for (i = 0; i < n; i++)
    x[i] = genrand_real1() * mx;
}
void rng_uniform_s(int n, float *x, float mx)
{
  int i;
  for (i = 0; i < n; i++)
    x[i] = (float) (genrand_real1() * mx);
}

void rng_gaussian_d(int n, double *x, double sig)
{
  int i;
  for (i = 0; i < n; i++)
    x[i] = ziggurat_gaussian() * sig;
}
void rng_gaussian_s(int n, float *x, float sig)
{
  int i;
  for (i = 0; i < n; i++)
    x[i] = (float) (ziggurat_gaussian() * sig);
}

void rng_init(unsigned long seed)
{
  init_by_array((uint32_t *) &seed, sizeof(seed) / sizeof(uint32_t));
  ziggurat_gaussian_set();
}
