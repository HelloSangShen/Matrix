//
//  matrix.h
//
//  Created by HelloSangShen on 2017/4/24.
//  Copyright © 2017年 HelloSangShen. All rights reserved.
//
#ifndef MATRIX__H
#define MATRIX__H

#include <iostream>
#include <vector>

class Matrix
{
private:
	// point to the data
	double** _data;
	// number of row and column
	size_t _nRow, _nCol;
	// flag to indicate row-first or column-first
	int _t;
	bool checkRange(size_t r, size_t c) const;
	void swap(Matrix& mat);
    

public:
	// construct a r-row and c-column matrix with all init element
	Matrix(size_t r, size_t c, double init);
	// copy constructor
	Matrix(const Matrix& mat);
	Matrix& operator=(Matrix mat);
	~Matrix();
	// get element at r-row and c-column
	// return reference to make it modifiable
	double& operator()(size_t r, size_t c) const;
	// get a submatrix [rs:re,cs:ce]
	Matrix subMatrix(size_t rs, size_t re, size_t cs, size_t ce) const;
	// output the matrix
	friend std::ostream& operator<<(std::ostream& out, const Matrix& rhs);
	size_t getNRow() const;
	size_t getNCol() const;
	std::vector<double> getRow(size_t r) const;
	std::vector<double> getCol(size_t c) const;
	bool setRow(size_t r, const std::vector<double>& d);
	bool setCol(size_t c, const std::vector<double>& d);
	// transpose it in-place
	Matrix& transpose();
};


#endif
