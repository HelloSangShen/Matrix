#ifndef FFT__H
#define FFT__H

#include <complex>
#include <vector>
#include <iostream>
#include <math.h>

size_t calcN(size_t length);
std::complex<double> pow(std::complex<double> base, int exponent);

// different function with different input
std::complex<double> wnk(size_t N, int k);
std::vector<std::complex<double> > fft(std::vector<int> data, size_t N=0);
std::vector<std::complex<double> > fft(std::vector<double> data, size_t N=0);
std::vector<std::complex<double> > fft(std::vector<std::complex<double> > data, size_t N=0) ;


#endif
