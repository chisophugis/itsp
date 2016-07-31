#include <vector>
#include <complex>
#include <math.h>
#include <stdlib.h>

std::complex<double> dtft(std::vector<double> &Vec, std::complex<double> ZInv) {
  // X(z) or X(omega) (i.e. X(exp(j omega)))
  std::complex<double> X = 0;
  for (int i = 0, e = Vec.size(); i != e; ++i) {
    double E = Vec[e - (i + 1)];
    X = E + ZInv * X;
  }
  return X;
}

int main(int argc, char **argv) {
  if (argc != 4)
    return 1;

  double omega1 = strtod(argv[1], 0);
  double omega2 = strtod(argv[2], 0);
  int N = strtol(argv[3], 0, 10);

  std::vector<double> Vec;
  double D;
  while (scanf("%lf", &D) == 1)
    Vec.push_back(D);

  double diff = (omega2 - omega1) / N;
  for (int i = 0; i != N; ++i) {
    auto ZInv = std::polar(1., -(omega1 + i * diff));
    auto X = dtft(Vec, ZInv);
    printf("%.17e %.17e\n", X.real(), X.imag());
  }

  return 0;
}
