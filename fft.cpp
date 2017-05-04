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

std::complex<double> wnk(size_t N, int k){
    
    double p = 2 * M_PI * k /N;
    return complex<double>(cos(p), -1 * sin(p));
}

vector<complex<double> >
fft(vector<complex<double> > data, size_t N) {

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
        res.push_back(wnk(2, 0)*data[0] + wnk(2, 0)*data[1]);
        res.push_back(wnk(2, 0)*data[0] + wnk(2, 1)*data[1]);
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
        vector<complex<double> > evenRes = fft(evenItems, N/2);
        vector<complex<double> > oddRes = fft(oddItems, N/2);
        
        // construct
        for(int i = 0; i < N/2; i++){
            res.push_back(evenRes[i] + wnk(N, i) * oddRes[i]);
        }
        for(int i = 0; i < N/2; i++){
            res.push_back(evenRes[i] - wnk(N, i) * oddRes[i]);
        }
    }
    
    return res;
}
