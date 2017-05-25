//  matrix.cpp
//
//  Created by HelloSangShen on 2017/5/12.
//  Copyright © 2017年 HelloSangShen. All rights reserved.
//

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

// calculate the fft/ifft of every row of the matrix
Matrix<std::complex<double> > fftRow(const Matrix<std::complex<double> >& mat, size_t row, size_t col, char patten);
// calculate the fft/ifft of the input vector
vector<std::complex<double> > calfft(vector<std::complex<double> > data, size_t N, char patten);

// fft of vector<int>
std::vector<std::complex<double> > fft(std::vector<int> data, size_t N=0);
// fft of vector<double>
std::vector<std::complex<double> > fft(std::vector<double> data, size_t N=0);
// fft of complex
std::vector<std::complex<double> > fft(std::vector<std::complex<double> > data, size_t N=0);
// ifft
std::vector<std::complex<double> > ifft(std::vector<std::complex<double> > data, size_t N=0);

// expand for fft 2d
Matrix<std::complex<double> > expand(const Matrix<std::complex<double> >& mat, size_t row, size_t col);

Matrix<std::complex<double> > fft2d(const Matrix<int>& mat, size_t row, size_t col);
Matrix<std::complex<double> > fft2d(const Matrix<double>& mat, size_t row, size_t col);
Matrix<std::complex<double> > fft2d(const Matrix<std::complex<double> >& mat, size_t row, size_t col);
Matrix<std::complex<double> > ifft2d(const Matrix<std::complex<double> >& mat, size_t row, size_t col);


#endif
