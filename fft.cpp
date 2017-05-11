#include "fft.h"

using std::complex;
using std::vector;

size_t calcN(size_t length) {
    // check if length is power of 2
    // if it is, just return length
    // if not, get the correct N and return
    if(0 == (length & (length-1))){
        return length;
    }
    
    vector<size_t> vec;
    while(length){
        vec.push_back(length);
        length = length >> 1;
    }
    
    size_t res = vec[0];
    for(int i = 1; i < vec.size(); i++){
        res |= vec[i];
    }
    return res + 1;
}

complex<double> pow(complex<double> base, int exponent) {
    // return base^{exponent}
    complex<double> res = base;
    for(int i = 1; i < exponent; i++){
        res *= base;
    }
    return res;
}


complex<double> wnk(size_t N, int k){
    
    double p = 2 * M_PI * k /N;
    return complex<double>(cos(p), -1 * sin(p));
}

complex<double> w_minusn_k(size_t N, int k){
    
    double p = -2 * M_PI * k /N;
    return complex<double>(cos(p), -1 * sin(p));
}


vector<complex<double> >
calfft(vector<complex<double> > data, size_t N, char patten) {

    // change length to make it beign just the power of 2
    N = calcN(N);
    // append 0 if necessary
    while (N > data.size()){
        data.push_back(complex<double>(0.0, 0.0));
    }
    // start fft
    // check if N is 0, 1, 2
    // if N is 0 or 1, just return data
    // if N is 2, do dft on them
    // if N > 2, do fft
    // 1. split input into two part
    // 2. do fft on them seperately
    // 3. construct result from output
    vector<complex<double> > res;
    if(N == 1 || N == 0){
        return data;
    }else if(N == 2){
        if(patten == 'i'){
            res.push_back(w_minusn_k(2, 0)*data[0] + w_minusn_k(2, 0)*data[1]);
            res.push_back(w_minusn_k(2, 0)*data[0] + w_minusn_k(2, 1)*data[1]);
        }else if(patten == 'f'){
            res.push_back(wnk(2, 0)*data[0] + wnk(2, 0)*data[1]);
            res.push_back(wnk(2, 0)*data[0] + wnk(2, 1)*data[1]);
        }
        return res;
    }else{
        // split
        vector<complex<double> > evenItems;
        vector<complex<double> > oddItems;
        for(int i = 0; i < data.size(); i++){
            if(i % 2 == 0){
                evenItems.push_back(data[i]);
            }else{
                oddItems.push_back(data[i]);
            }
        }
        
        // fft seperately
        vector<complex<double> > evenRes = calfft(evenItems, N/2, patten);
        vector<complex<double> > oddRes = calfft(oddItems, N/2, patten);
        
        // construct
        for(int i = 0; i < N/2; i++){
            if(patten == 'i'){
                res.push_back(evenRes[i] + w_minusn_k(N, i) * oddRes[i]);
            }else if(patten == 'f'){
                res.push_back(evenRes[i] + wnk(N, i) * oddRes[i]);
            }
        }
        for(int i = 0; i < N/2; i++){
            if(patten == 'i'){
                res.push_back(evenRes[i] - w_minusn_k(N, i) * oddRes[i]);
            }else if(patten == 'f'){
                res.push_back(evenRes[i] - wnk(N, i) * oddRes[i]);
            }
        }
    }
    
    return res;
}
vector<complex<double> >
fft(vector<int> data, size_t N)
{
    // convert data to vector<complex<double> >
    // call:
    // vector<complex<double> >
    // fft(vector<complex<double> > data, size_t N)
    vector<complex<double> > complexData;
    
    for(int i = 0; i < N; i++){
        complexData.push_back(complex<double>(data[i], 0.0));
    }
    return fft(complexData, N);
}

vector<complex<double> >
fft(vector<double> data, size_t N)
{
    // convert data to vector<complex<double> >
    // call:
    // vector<complex<double> >
    // fft(vector<complex<double> > data, size_t N)
    vector<complex<double> > complexData;
    
    for(int i = 0; i < N; i++){
        complexData.push_back(complex<double>(data[i], 0.0));
    }
    
    return fft(complexData, N);
}

vector<complex<double> >
ifft(vector<complex<double> > data, size_t N){
    std::vector<complex<double> > res =  calfft(data, N, 'i');
    for(int i = 0; i < res.size(); i++){
        res.at(i) /= calcN(N);
    }
    return res;
}

vector<complex<double> >
fft(vector<complex<double> > data, size_t N){
    return calfft(data, N, 'f');
}

Matrix<complex<double> >
fftRow(const Matrix<std::complex<double> >& mat, size_t row, size_t col, char patten){
  
    //calculate every row of the matrix
    Matrix<complex<double> > newMat(row, col, complex<double>(0, 0));
    for(int i = 0; i < row; i++){
        vector<complex<double>> vecRow;
        if(patten == 'f'){
            vecRow = fft(mat.getRow(i), col);
        }else if(patten == 'i'){
            vecRow = ifft(mat.getRow(i), col);
        }
        if(!newMat.setRow(i, vecRow)){
            //cout << "set failed!" << endl;
        };
    }
    return newMat;
}

Matrix<complex<double> >
fft2d(const Matrix<int>& mat, size_t row, size_t col){
    Matrix<std::complex<double> > comMat(row, col, complex<double>(0, 0));
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            comMat(i, j) = complex<double>(mat(i, j), 0);
        }
    }
    return fft2d(comMat, row, col);
    
}
Matrix<complex<double> >
fft2d(const Matrix<double>& mat, size_t row, size_t col){
    Matrix<std::complex<double> > comMat(row, col, complex<double>(0, 0));
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            comMat(i, j) = complex<double>(mat(i, j), 0);
        }
    }
    return fft2d(comMat, row, col);
}

Matrix<complex<double> >
expand(const Matrix<complex<double> >& mat, size_t row, size_t col){
    size_t tempRow = calcN(row);
    size_t tempCol = calcN(col);
    Matrix<complex<double> > m(tempRow, tempCol, complex<double>(0, 0));
    
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            m(i, j) = mat(i, j);
        }
    }
    return m;
}

Matrix<complex<double> >
fft2d(const Matrix<complex<double> >& mat, size_t row, size_t col){
    Matrix<complex<double> > m = expand(mat, row, col);
    return fftRow(fftRow(m, calcN(row), calcN(col), 'f').transpose(),calcN(row), calcN(col), 'f').transpose();
}

Matrix<complex<double> >
ifft2d(const Matrix<complex<double> >& mat, size_t row, size_t col){
    Matrix<complex<double> > m = expand(mat, row, col);
    Matrix<complex<double> > res = fftRow(fftRow(m, calcN(row), calcN(col), 'i').transpose(),
                                          calcN(row), calcN(col), 'i').transpose();
    return res;
}
