#ifndef __RNG_H
#define __RNG_H

void rng_uniform_i(int n, int *x, int mx);
void rng_uniform_d(int n, double *x, double mx);
void rng_uniform_s(int n, float *x, float mx);

void rng_gaussian_d(int n, double *x, double sig);
void rng_gaussian_s(int n, float *x, float sig);

void rng_init(unsigned long seed);

#endif /* __RNG_H */
