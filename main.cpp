#include "matrix.h"
#include <iostream>
#include <vector>
#include <stdexcept>

using std::cout;
using std::endl;
using std::vector;
using std::range_error;

void test_matrix();

int main()
{
	test_matrix();
	return 0;
}

void test_matrix()
{
	cout << "------------------------------------" << endl;
	cout << "test of constructor:" << endl;
	cout << "------------------------------------" << endl;
	Matrix m(5,4,7.9);
	cout << "*******    m:\n" << m << endl;
    cout << "------------------------------------" << endl;
    cout << "test of copy-constructor:" << endl;
    cout << "------------------------------------" << endl;
	Matrix mC(m);
	cout << "*******    mC:\n" << mC << endl;
    cout << "------------------------------------" << endl;
    cout << "test of operator=:" << endl;
    cout << "------------------------------------" << endl;
	Matrix mE = m;
	cout << "*******    mE:\n" << mE << endl << endl;
    cout << "address of m："<<&m <<endl;
    cout << "address of mC："<<&mC <<endl;
    cout << "adress of mE："<<&mE <<endl;
    if(&m != &mC && &m != &mE && &mE != &mC)
        cout << "different instances!" << endl << endl;
    
    cout << "------------------------------------" << endl;
    cout << "test of operator()" << endl;
	cout << "------------------------------------" << endl;
	mC(1,2) = 2;
	cout << "*******  mC:\n" << mC << endl;
	mE(2,0) = 7;
	cout << "*******  mE:\n" << mE << endl;
	cout << "*******  m:\n" << m << endl;
    
    cout << "get mE(2, 0):" << endl;
    cout << mE(2, 0) << endl;
	cout << "------------------------------------" << endl << endl;
	cout << "test of transpose()" << endl;
	cout << "------------------------------------" << endl;
	cout << "*******  transpose mE:\n" << mE.transpose() << endl;
    cout << "get mE(0, 2):" << endl;
    cout << mE(0, 2) << endl;
    
	cout << "------------------------------------" << endl;
	cout << "test of get and set" << endl;
	cout << "------------------------------------" << endl;
    vector<double> vd = mE.getRow(0);
	cout << "get the first row of mE:" << endl;
	for(size_t i = 0; i < vd.size(); ++i)
		cout << vd.at(i) << "  **  ";
	cout << endl;
	vd.at(1) = -3.3;
    for(size_t i = 0; i < vd.size(); ++i)
        cout << vd.at(i) << "  **  ";
    cout << endl;
    mC.setCol(3, vd);
	cout << "*******  mC:\n" << mC << endl;
	cout << "------------------------------------" << endl << endl;
    
    vector<double> vt = mE.getCol(0);
    cout << "get the first col of mE:" << endl;
    for(size_t i = 0; i < vt.size(); ++i)
        cout << vt.at(i) << "  **  ";
    cout << endl;
    vt.at(1) = -3.3;
    for(size_t i = 0; i < vt.size(); ++i)
        cout << vt.at(i) << "  **  ";
    cout << endl;
    mC.setRow(3, vt);
    cout << "*******  mC:\n" << mC << endl;
    cout << "------------------------------------" << endl << endl;
    
    cout << "test of subMatrix" << endl;
	cout << "------------------------------------" << endl;
	cout << "*******  mC.subMatrix(1,3,1,3):\n" << mC.subMatrix(1,3,1,3) << endl;
}
