#include "fft.h"
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

	vector<double> a;
	a.push_back(1.);
	a.push_back(2.);
	a.push_back(3.);
    a.push_back(4.);
    a.push_back(5.);
    a.push_back(6.);
    a.push_back(7.);
	vector<complex<double> > r = fft(a, 7);
	for(size_t i=0; i<r.size(); ++i)
        cout << r.at(i) << "\t";
    cout<< endl;
}
