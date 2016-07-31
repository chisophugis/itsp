#include <algorithm>
#include <complex>
#include <vector>

#include <math.h>
#include <stdlib.h>

using cdouble = std::complex<double>;
template <typename T>
using Vec = std::vector<T>;

const double Pi = 3.141592653589793;
const double TwoPi = 6.283185307179586;

Vec<cdouble> fftRecurse(Vec<cdouble> &V, int Begin, int End,
                        int NTot) {
  int N = End - Begin;
  if (N == 1)
    return {V[Begin]};

  int Half = N / 2;
  Vec<cdouble> FirstHalf = fftRecurse(V, Begin, Begin + Half, NTot);
  Vec<cdouble> SecondHalf = fftRecurse(V, Begin + Half, End, NTot);

  Vec<cdouble> Ret(N);
  for (int i = 0; i != Half; ++i) {
    Ret[i] = FirstHalf[i] + std::polar(1., (-TwoPi / N) * i) * SecondHalf[i];
    Ret[Half + i] = FirstHalf[i] +
                    std::polar(1., (-TwoPi / N) * (Half + i)) * SecondHalf[i];
  }
  return Ret;
}

void intersperse(const Vec<cdouble> &Big, Vec<cdouble> &First,
                 Vec<cdouble> &Second) {
  // First.size() = Second.size() = Big.size() / 2
  for (int i = 0, e = Big.size() / 2; i != e; ++i) {
    First[i] = Big[2 * i];
    Second[i] = Big[2 * i + 1];
  }
}

Vec<cdouble> fftShuffle(const Vec<cdouble> &V) {
  int N = V.size();
  if (N == 1)
    return {V[0]};
  Vec<cdouble> First(N / 2), Second(N / 2);
  intersperse(V, First, Second);
  First = fftShuffle(First);
  Second = fftShuffle(Second);
  Vec<cdouble> Ret(N);
  for (int i = 0; i != N / 2; ++i) {
    Ret[i] = First[i];
    Ret[N / 2 + i] = Second[i];
  }
  return Ret;
}

// V.size() must be a power of 2!
Vec<cdouble> fft(const Vec<cdouble> &V) {
  Vec<cdouble> ShufV = fftShuffle(V);
  return fftRecurse(ShufV, 0, ShufV.size(), ShufV.size());
}

int main(int, char **) {

  Vec<cdouble> V;
  double Re;
  double Im;
  while (scanf("%lf %lf", &Re, &Im) == 2)
    V.push_back(cdouble(Re, Im));

  // Check for power of 2.
  if ((V.size() & (V.size() - 1)) != 0)
    return 1;
  //while ((V.size() & (V.size() - 1)) != 0)
  //  V.push_back(cdouble(0, 0));

  Vec<cdouble> DFT = fft(V);

  for (int i = 0, e = DFT.size(); i != e; ++i)
    printf("%+.17e %+.17e\n", DFT[i].real(), DFT[i].imag());

  return 0;
}
