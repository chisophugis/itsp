#include <stdio.h>
#include <stdlib.h>


double fir(int M, double *h, double *w, double x) {

  w[0] = x;

  double y = 0.;
  for (int i = 0; i <= M; i++)
    y += w[i] * h[i];

  for (int i = M; i > 0; i--)
    w[i] = w[i - 1];

  return y;
}

int main(int argc, char **argv) {
  // Usage: ./fir <impulse response>
  // Example: ./fir 1. 1. 1. 1.

  // Impulse response length.
  const int IRLen = argc - 1;

  if (IRLen < 1)
    return 1;

  // M = filter order. (one less than IR length)
  const int M = IRLen - 1;

  double *h = (double*)calloc(IRLen, sizeof(double));
  for (int i = 1; i != argc; ++i)
    if (sscanf(argv[i], "%lf", &h[i-1]) != 1)
      return 1;

  // w[0] is just a dummy location where we shift the next input into,
  // which makes some things slightly more convenient.
  // Only M samples of memory are actually in the filter.
  double *w = (double*)calloc(IRLen, sizeof(double));

  double x, y;
  while (fscanf(stdin, "%lf", &x) == 1) {
    y = fir(M, h, w, x);
    fprintf(stdout, "%lf\n", y);
  }

  /* Input-off transient. */
  for (int i = 0; i < M; i++) {
    y = fir(M, h, w, 0.);
    fprintf(stdout, "%lf\n", y);
  }

  return 0;
}

