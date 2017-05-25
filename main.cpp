//  matrix.cpp
//
//  Created by HelloSangShen on 2017/4/26.
//  Copyright © 2017年 HelloSangShen. All rights reserved.
//

#include "fft.h"
#include "matrixTemplate.h"
#include <iostream>
using namespace std;

void test_fft();

int main()
{
	test_fft();
	return 0;
}

void test_fft()
{

//    cout << "------------------------complex------------------------" << endl;
//    Matrix<complex<double> > mat1(4, 4, complex<double>(1.2,1));
//    cout << mat1 <<endl;
//    
//    Matrix<complex<double> > fftMat1 = fft2d(mat1, 4, 4);
//    cout << fftMat1 << endl;
//    
//    Matrix<complex<double> > matTest(4, 4, complex<double>(0,0));
//    for(int i = 0; i < 4; i++){
//        for(int j = 0; j < 4; j++){
//            matTest(i, j) = complex<double>(i, j);
//        }
//    }
//    cout << matTest <<endl;
//    
//    Matrix<complex<double> > fftMatTest = fft2d(matTest, 4, 4);
//    cout << fftMatTest << endl;
//    
//    
//    cout << "-------------------------------------------------------" << endl;
//
//    
//    
//    
//    cout << "------------------------double-------------------------" << endl;
//    Matrix<double > mat2(4, 4, 1.2);
//    cout << mat2 <<endl;
//    
//    Matrix<complex<double> > fftMat2 = fft2d(mat2, 4, 4);
//    cout << fftMat2 << endl;
//    cout << "-------------------------------------------------------" << endl;
//    
//    
//    
//    
//    cout << "-------------------------int---------------------------" << endl;
//    Matrix<int> mat3(4, 4, 1);
//    cout << mat3 <<endl;
//    
//    Matrix<complex<double> > fftMat3 = fft2d(mat3, 4, 4);
//    cout << fftMat3 << endl;
//    cout << "-------------------------------------------------------" << endl;
    
    
//    cout << "-------------------------ifft---------------------------" << endl;
//    Matrix<complex<double> > matTest(5, 5, complex<double>(0,0));
//    for(int i = 0; i < 5; i++){
//        for(int j = 0; j < 5; j++){
//            matTest(i, j) = complex<double>(i, j);
//        }
//    }
//    cout << matTest <<endl;
//    
//    Matrix<complex<double> > fftMatTest = fft2d(matTest, 5, 5);
//    cout << fftMatTest << endl;
//    
//    Matrix<complex<double> > ifftMatTest = ifft2d(fftMatTest, 8, 8);
//    cout << ifftMatTest << endl;
//    cout << "-------------------------------------------------------" << endl;

    Matrix<double> a(4, 9, 0);
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 9; j++){
            a(i, j) = i * j;
        }
    }
    
    cout << a << endl;
    a.transpose();
    cout << a << endl;
    a.transpose();
    cout << a << endl;
    
}
