//
//  matrix.cpp
//
//  Created by HelloSangShen on 2017/4/26.
//  Copyright © 2017年 HelloSangShen. All rights reserved.
//
#include "matrix.h"
#include <stdexcept>
#include <iostream>

using std::range_error;
using std::vector;
using std::cout;
using std::endl;
using std::ostream;

Matrix::Matrix(size_t r, size_t c, double init):
_nRow(r), _nCol(c), _t(0)
{
	// new _data
	// new _data[i] within loop

    _t = 1;
    
    _data = new double* [r];

    for(int i = 0; i < r; i++){
        _data[i] = new double[c];
    }
    
    for(int i = 0; i < r ; i++){
        for (int j = 0; j < c; j++) {
            _data[i][j] = init;
        }
    }
}

Matrix::Matrix(const Matrix& mat):
_nRow(mat._nRow), _nCol(mat._nCol), _t(mat._t)
{
	// new _data
	// new and assign _data[i] within loop
    _data = new double* [_nRow];
    
    for(int i = 0; i < _nRow; i++){
        _data[i] = new double[_nCol];
    }
    
    for(int i = 0; i < _nRow ; i++){
        for (int j = 0; j < _nCol; j++) {
            _data[i][j] = mat._data[i][j];
        }
    }
}

Matrix::~Matrix()
{
    // delete _data[i] first
    // then delete _data
    
    for (int i = 0; i < _nRow; i++) {
        delete _data[i];
    }
    delete _data;
}

void Matrix::swap(Matrix& mat) {
    std::swap(_data, mat._data);
	std::swap(_nRow, mat._nRow);
	std::swap(_nCol, mat._nCol);
    std::swap(_t, mat._t);
}

Matrix& Matrix::operator=(Matrix mat)
{
	swap(mat);
	return *this;
}

size_t Matrix::getNRow() const
{
	// return the number of row
    if(_t == 1)
        return _nRow;
    return _nCol;
}

size_t Matrix::getNCol() const
{
	// return the number of column
    if(_t == 0)
        return _nRow;
    return _nCol;
}

bool Matrix::checkRange(size_t r, size_t c) const
{
	// check if r-row and c-column is out of range
    if(_t == 1){
        if(r >= _nRow || c >= _nCol)
            return false;
    }else if(_t == 0){
        if(r >= _nCol || c >= _nRow)
            return false;
    }
    
    return true;
}

double& Matrix::operator()(size_t r, size_t c) const
{
	// get element in (r,c)
	// remember check first
	// different of _t has different order
    if(!checkRange(r, c)){
        // out of range
        throw range_error("operator() :    Out Of Range");
    }
    
    if(_t == 1){
        return _data[r][c];
    }else{
        return _data[c][r];
    }
}

Matrix Matrix::subMatrix(size_t rs, size_t re, size_t cs, size_t ce) const
{
	// note the validity of value:rs, re, cs, ce
	// try to use "except" to broadcast the exception
    
    if(_t == 1){
        if(!(rs <= re && re < _nRow && cs <= ce && ce < _nCol)){
            // out of range
            throw range_error("subMatrix :    Parameters Out Of Range");
        }else{
            Matrix newMat =  Matrix(re - rs + 1, ce - cs + 1, 0);
            for(int i = 0; i < newMat._nRow; i++){
                for(int j = 0; j < newMat._nCol; j++){
                    newMat._data[i][j] = _data[i + rs][j + cs];
                }
            }
            return newMat;
        }
    }else {
        if(!(rs <= re && re <= _nCol && cs <= ce && ce <= _nRow)){
            // out of range
            throw range_error("subMatrix :    Parameters Out Of Range");
        }else{
            Matrix newMat =  Matrix(ce - cs + 1, re - rs + 1, 0);
            for(int i = 0; i < newMat._nRow; i++){
                for(int j = 0; j < newMat._nCol; j++){
                    // ...
                    newMat._data[i][j] = _data[i + cs][j + rs];
                }
            }
            return newMat;
        }
    }
    
    return Matrix(1,1,0);
}


std::vector<double> Matrix::getRow(size_t r) const
{
	// get all element in r-row and push it back in a vector
	// remember check range first
    if((_t == 1 && r > _nRow) || (_t == 0 && r > _nCol)){
        throw range_error("getRow() :    Out Of Range");
    }
    vector<double> vec;
    if(_t == 1){
        for(int i = 0; i < _nCol; i++){
            vec.push_back(_data[r][i]);
        }
    }else{
        for(int i = 0; i < _nRow; i++){
            vec.push_back(_data[i][r]);
        }
    }
    return vec;
}

std::vector<double> Matrix::getCol(size_t c) const
{
	// get all element in c-column and push it back in a vector
	// remember check range first
    if((_t == 1 && c > _nCol) || (_t == 0 && c > _nRow)){
        throw range_error("getCol() :    Out Of Range");
    }
    vector<double> vec;
    if(_t == 1){
        for(int i = 0; i < _nRow; i++){
            vec.push_back(_data[i][c]);
        }
    }else{
        for(int i = 0; i < _nCol; i++){
            vec.push_back(_data[c][i]);
        }
    }
    return vec;
}

bool Matrix::setRow(size_t r, const vector<double>& d)
{
	// set the element of the r-row
	// remember check range first
        
    if(_t == 1 && checkRange(r, d.size() - 1)){
        if(d.size() == _nCol){
            for(int i = 0; i < d.size(); i++){
                _data[r][i] = d[i];
            }
            return true;
        }else{
            throw range_error("setRow :    illegal size of vector");
        }
    }else if(_t == 0 && checkRange(d.size() - 1, r)){
        if(d.size() == _nRow){
            for(int i = 0; i < d.size(); i++){
                _data[i][r] = d[i];
            }
            return true;
        }else{
            throw range_error("setRow :    illegal size of vector");}
    }
    return false;
}

bool Matrix::setCol(size_t c, const vector<double>& d)
{
	// set the element of the c-column
	// remember check range first
    
    if(_t == 1 && checkRange(d.size() - 1, c)){
        if(d.size() == _nRow){
            for(int i = 0; i < d.size(); i++){
                _data[i][c] = d.at(i);
            }
            return true;
        }else{
            throw range_error("setRow :    illegal size of vector");
        }
    }else if(_t == 0 && checkRange(c, d.size() - 1)){
        if (d.size() == _nCol) {
            for(int i = 0; i < d.size(); i++){
                _data[c][i] = d.at(i);
            }
            return true;
        }else{
            throw range_error("setRow :    illegal size of vector");
        }
    }
    return false;
}

Matrix& Matrix::transpose()
{
	// change _t
	// swap _nRow and _nCol
    // the fastest transpose in the history ?
    
    if(_t == 0){
        _t = 1;
    }else{
        _t = 0;
    }
    
    return * this;
}

ostream& operator<<(ostream& out, const Matrix& rhs)
{
	for(size_t i = 0; i < rhs.getNRow(); ++i) {
		for(size_t j = 0; j < rhs.getNCol(); ++j) {
            out << rhs(i,j) << "\t";
        }
        out << endl;
    }
    return out;
}
