// DTFT at a single point.
#include <vector>
#include <complex>
#include <math.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc != 2)
    return 1;

  double omega = strtod(argv[1], 0);
  auto ZInv = std::polar(1., -omega);

  // %+.13la is good because it shows all signficant hex digits and no
  // extra ones.
  printf("%+.13la %+.13la\n", ZInv.real(), ZInv.imag());

  std::vector<double> Vec;
  double D;
  while (scanf("%lf", &D) == 1)
    Vec.push_back(D);

  // X(z) or X(omega) (i.e. X(exp(j omega)))
  std::complex<double> X = 0;
  for (int i = 0, e = Vec.size(); i != e; ++i) {
    double E = Vec[e - (i + 1)];
    X = E + ZInv * X;
  }

  printf("%+.17le %+.17le\n", X.real(), X.imag());

  return 0;
}
