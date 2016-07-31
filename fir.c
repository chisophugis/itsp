#include <stdio.h>

enum { M = 3 };

double fir(int M, double *h, double *w, double x) {
  int i;
  double y = 0.;

  w[0] = x;

  for (i = 0; i <= M; i++) {
    y += w[i] * h[i];
  }

  for (i = M; i > 0; i--) {
    w[i] = w[i - 1];
  }

  return y;
}

int main() {
  int i;
  double x;
  double y;
  double h[4] = {1.,1.,1.,1.};
  double w[4] = {0};

  while (fscanf(stdin, "%lf", &x) == 1) {
    y = fir(M, h, w, x);
    fprintf(stdout, "%lf\n", y);
  }

  /* Input-off transient. */
  for (i = 0; i < M; i++) {
    y = fir(M, h, w, 0.);
    fprintf(stdout, "%lf\n", y);
  }

  return 0;
}

