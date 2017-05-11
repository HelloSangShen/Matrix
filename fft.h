#ifndef FFT__H
#define FFT__H

#include <complex>
#include <vector>
#include <iostream>
#include <math.h>
#include "matrixTemplate.h"

size_t calcN(size_t length);

std::complex<double> wnk(size_t N, int k);
std::complex<double> w_minusn_k(size_t N, int k);

Matrix<std::complex<double> > fftRow(const Matrix<std::complex<double> >& mat, size_t row, size_t col, char patten);
vector<std::complex<double> > calfft(vector<std::complex<double> > data, size_t N, char patten);

std::vector<std::complex<double> > fft(std::vector<int> data, size_t N=0);
std::vector<std::complex<double> > fft(std::vector<double> data, size_t N=0);
std::vector<std::complex<double> > fft(std::vector<std::complex<double> > data, size_t N=0);
std::vector<std::complex<double> > ifft(std::vector<std::complex<double> > data, size_t N=0);

Matrix<std::complex<double> > expand(const Matrix<std::complex<double> >& mat, size_t row, size_t col);

Matrix<std::complex<double> > fft2d(const Matrix<int>& mat, size_t row, size_t col);
Matrix<std::complex<double> > fft2d(const Matrix<double>& mat, size_t row, size_t col);
Matrix<std::complex<double> > fft2d(const Matrix<std::complex<double> >& mat, size_t row, size_t col);
Matrix<std::complex<double> > ifft2d(const Matrix<std::complex<double> >& mat, size_t row, size_t col);


#endif
