These are various random programs I wrote while reading the book
"Introduction to Signal Processing" by Sophocles J. Orfanidis.

This is the best and most practical book on signal processing I have
found. It really gives insight into the whole signal acquisition and
reproduction pipeline.

Additionally, this is the only resource I have found which gives a
proper explanation of oversampling, noise shaping, and related
concepts.
(I was pondering doing something with some SPM1437 microphones I had
around and I couldn't find a good resource that would explain the
intuition/understanding for how to use their PDM output. This book
does.).

Also, Chapter 9 "DFT/FFT algorithms" is incredibly insightful.
It starts with just computing the DTFT at a single frequency.
Then it shows how the FFT is an efficient way to compute the DTFT at
multiple (evenly spaced) frequencies.
This makes it obvious why you can zero-pad at the end of a signal.
Section 9.3 on "Physical versus Computational Resolution" is extremely
insightful.


Original modification times:

-rw-rw-r-- 1 sean sean     594 Apr 29  2015 fir.c
-rw-rw-r-- 1 sean sean    1169 Apr 29  2015 fir.cpp
-rw-rw-r-- 1 sean sean     499 May 31  2015 requant.cpp
-rw-rw-r-- 1 sean sean     735 Jun  6  2015 dtft.cpp
-rw-rw-r-- 1 sean sean     850 Jun  6  2015 dtftr.cpp
-rw-rw-r-- 1 sean sean    2139 Jun  7  2015 fft.cpp
-rw-rw-r-- 1 sean sean    2877 Jun  7  2015 fftbench.cpp
