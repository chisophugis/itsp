#include <algorithm>
#include <chrono>
#include <complex>
#include <random>
#include <vector>

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

using cdouble = std::complex<double>;
template <typename T>
using Vec = std::vector<T>;

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
    cdouble S = std::polar(1., (-TwoPi / N) * i) * SecondHalf[i];
    Ret[i] = FirstHalf[i] + S;
    Ret[Half + i] = FirstHalf[i] - S;
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
  int N = V.size();
  Vec<cdouble> ShufV = fftShuffle(V);
  return fftRecurse(ShufV, 0, ShufV.size(), ShufV.size());
}

int64_t nanos() {
  using namespace std::chrono;
  auto Duration = high_resolution_clock::now().time_since_epoch();
  return duration_cast<nanoseconds>(Duration).count();
}

struct TimeBlock {
  TimeBlock(const char *Name) : Name(Name) { BeginNanos = nanos(); }
  void end() {
    int64_t EndNanos = nanos();
    int64_t Elapsed = EndNanos - BeginNanos;
    printf("%-10s: %.17lf\n", Name, double(Elapsed) / 1.e3);
  }
  const char *Name;
  int64_t BeginNanos;
};

int main(int, char **) {

  std::random_device RD;
  std::mt19937 Gen(RD());
  std::uniform_real_distribution<double> Dist{0, 1};

  enum { kBenchSize = 1 << 18 };

  TimeBlock TAllocate("Allocate");
  Vec<cdouble> V(kBenchSize);
  TAllocate.end();

  TimeBlock TGenerate("Generate");
  for (int i = 0; i != kBenchSize; ++i)
    V[i] = Dist(Gen);
  TGenerate.end();

  //for (int i = 0, e = V.size(); i != e; ++i)
  //  printf("%+.17e %+.17e\n", V[i].real(), V[i].imag());

  // Check for power of 2.
  if ((V.size() & (V.size() - 1)) != 0)
    return 1;

  TimeBlock TFFT("FFT");
  Vec<cdouble> DFT = fft(V);
  TFFT.end();

  //for (int i = 0, e = DFT.size(); i != e; ++i)
  //  printf("%+.17e %+.17e\n", DFT[i].real(), DFT[i].imag());

  return 0;
}
