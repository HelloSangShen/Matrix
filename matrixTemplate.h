//
//  matrixTemplate.h
//
//  Created by HelloSangShen on 2017/4/27.
//  Copyright © 2017年 HelloSangShen. All rights reserved.
//

#ifndef matrixTemplate_h
#define matrixTemplate_h

#include <iostream>
#include <vector>
#include <stdexcept>

using std::range_error;
using std::vector;
using std::cout;
using std::endl;
using std::ostream;

template<typename T>
class Matrix
{
private:
    // point to the data
    T ** _data;
    // number of row and column
    size_t _nRow, _nCol;
    // flag to indicate row-first or column-first
    int _t;
    bool checkRange(size_t r, size_t c) const;
    void swap(Matrix& mat);
    
public:
    // construct a r-row and c-column matrix with all init element
    Matrix(size_t r, size_t c, T init);
    // copy constructor
    Matrix(const Matrix<T>& mat);
    Matrix<T>& operator=(Matrix<T> mat);
    ~Matrix();
    // get element at r-row and c-column
    // return reference to make it modifiable
    T& operator()(size_t r, size_t c) const;
    // get a submatrix [rs:re,cs:ce]
    Matrix<T> subMatrix(size_t rs, size_t re, size_t cs, size_t ce) const;
    // output the matrix
    template<typename U>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<U>& rhs);
    size_t getNRow() const;
    size_t getNCol() const;
    std::vector<T> getRow(size_t r) const;
    std::vector<T> getCol(size_t c) const;
    bool setRow(size_t r, const std::vector<T>& d);
    bool setCol(size_t c, const std::vector<T>& d);
    // transpose it in-place
    Matrix<T>& transpose();
    
    // operator +
    Matrix<T> operator+(Matrix<T>& otherMat) const;
    Matrix<T> operator+(T factor) const;
    
    template<typename U>
    friend Matrix<U> operator+(const U factor, Matrix<U>& mat);
    
    // operator -
    Matrix<T> operator-(Matrix<T>& otherMat) const;
    Matrix<T> operator-(T factor) const;
    
    template<typename U>
    friend Matrix<U> operator-(const U factor, Matrix<U> & mat);
    
    // operator *
    Matrix<T> operator*(Matrix<T>& otherMat) const;
    T mul(vector<T> vec1, vector<T> vec2) const;
    
    Matrix<T> operator*(T factor) const;
    
    template<typename U>
    friend Matrix<U> operator*(const U factor, Matrix<U> & mat);

    // operator /
    template<typename U>
    friend Matrix<U> operator/(Matrix<U>& mat, const U factor);
};

template<typename T>
Matrix<T>::Matrix(size_t r, size_t c, T init):
_nRow(r), _nCol(c), _t(0)
{
    // new _data
    // new _data[i] within loop
    
    _t = 1;
    
    _data = new T* [r];
    
    for(int i = 0; i < r; i++){
        _data[i] = new T[c];
    }
    
    for(int i = 0; i < r ; i++){
        for (int j = 0; j < c; j++) {
            _data[i][j] = init;
        }
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& mat):
_nRow(mat._nRow), _nCol(mat._nCol), _t(mat._t)
{
    // new _data
    // new and assign _data[i] within loop
    _data = new T* [_nRow];
    
    for(int i = 0; i < _nRow; i++){
        _data[i] = new T[_nCol];
    }
    
    for(int i = 0; i < _nRow ; i++){
        for (int j = 0; j < _nCol; j++) {
            _data[i][j] = mat._data[i][j];
        }
    }
}

template<typename T>
Matrix<T>::~Matrix()
{
    // delete _data[i] first
    // then delete _data
    
    for (int i = 0; i < _nRow; i++) {
        delete _data[i];
    }
    delete _data;
}

template<typename T>
void Matrix<T>::swap(Matrix<T>& mat) {
    std::swap(_data, mat._data);
    std::swap(_nRow, mat._nRow);
    std::swap(_nCol, mat._nCol);
    std::swap(_t, mat._t);
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T> mat)
{
    swap(mat);
    return *this;
}


template<typename T>
size_t Matrix<T>::getNRow() const
{
    // return the number of row
    if(_t == 1)
        return _nRow;
    return _nCol;
}

template<typename T>
size_t Matrix<T>::getNCol() const
{
    // return the number of column
    if(_t == 0)
        return _nRow;
    return _nCol;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T>& otherMat) const
{
    
    if(otherMat.getNRow() == getNRow() && otherMat.getNCol() == getNCol()){
        Matrix<T> matRes = otherMat;
        
        for(int i = 0; i < getNRow(); i++){
            // This is not the best, I wana a better method
            vector<T> row = getRow(i);
            for(int j = 0; j < getNCol(); j++){
                matRes(i, j) = row[j] + otherMat(i, j);
            }
        }
        return matRes;
    }else{
        throw range_error("operator+ :    Range Error");
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator+(T factor) const
{
    Matrix<T> matRes = *this;
    for(int i = 0; i < getNRow(); i++){
        for(int j = 0; j < getNCol(); j++){
            matRes(i, j) = this->operator()(i, j) + factor;
        }
    }
    return matRes;
}

template<typename U>
Matrix<U> operator+(const U factor, Matrix<U>& mat)
{
    return mat + factor;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T>& otherMat) const{

    if(otherMat.getNRow() == getNRow() && otherMat.getNCol() == getNCol()){
        Matrix<T> matRes = otherMat;
        
        for(int i = 0; i < getNRow(); i++){
            // This is not the best, I wana a better method
            vector<T> row = getRow(i);
            for(int j = 0; j < getNCol(); j++){
                matRes(i, j) = row[j] - otherMat(i, j);
            }
        }
        return matRes;
    }else{
        throw range_error("operator+ :    Range Error");
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator-(T factor) const
{
    Matrix<T> matRes = *this;
    for(int i = 0; i < getNRow(); i++){
        for(int j = 0; j < getNCol(); j++){
            matRes(i, j) = this->operator()(i, j) - factor;
        }
    }
    return matRes;
}

template<typename U>
Matrix<U> operator-(const U factor, Matrix<U>& mat)
{
    Matrix<U> matRes = mat;
    for(int i = 0; i < mat.getNRow(); i++){
        for(int j = 0; j < mat.getNCol(); j++){
            matRes(i, j) = factor - mat(i, j);
        }
    }
    return matRes;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T>& otherMat) const{
    
    if(otherMat.getNRow() == getNCol()){
        // It is terrible, ugly
        Matrix<T> matRes = Matrix(getNRow(), otherMat.getNCol(), otherMat(0,0));
        
        for(int i = 0; i < getNRow(); i++){
            for(int j = 0; j < otherMat.getNCol(); j++){
                matRes(i, j) = mul(getRow(i), otherMat.getCol(j));
            }
        }
        return matRes;
    }else{
        throw range_error("operator+ :    Range Error");
    }
}

template<typename T>
T Matrix<T>::mul(vector<T> vec1, vector<T> vec2) const{
    
    if(vec1.size() != vec2.size()){
        throw range_error("operator* :    Size Error");
    }
    else{
        // ...
        T t = vec1[0] * vec2[0];
        for(int i = 1; i < vec1.size(); i++)
            t += vec1[i] * vec2[i];
        return t;
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator*(T factor) const
{
    Matrix<T> matRes = *this;
    for(int i = 0; i < getNRow(); i++){
        for(int j = 0; j < getNCol(); j++){
            matRes(i, j) = this->operator()(i, j) * factor;
        }
    }
    return matRes;
}

template<typename U>
Matrix<U> operator*(const U factor, Matrix<U>& mat)
{
    return mat * factor;
}

template<typename U>
Matrix<U> operator/(Matrix<U>& mat, const U factor)
{
    Matrix<U> matRes = mat;
    for(int i = 0; i < mat.getNRow(); i++){
        for(int j = 0; j < mat.getNCol(); j++){
            matRes(i, j) = mat(i, j)/factor;
        }
    }
    return matRes;
}


template<typename T>
bool Matrix<T>::checkRange(size_t r, size_t c) const
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

template<typename T>
T& Matrix<T>::operator()(size_t r, size_t c) const
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

template<typename T>
Matrix<T> Matrix<T>::subMatrix(size_t rs, size_t re, size_t cs, size_t ce) const
{
    // note the validity of value:rs, re, cs, ce
    // try to use "except" to broadcast the exception
    
    if(_t == 1){
        if(!(rs <= re && re < _nRow && cs <= ce && ce < _nCol)){
            // out of range
            throw range_error("subMatrix :    Parameters Out Of Range");
        }else{
            Matrix<T> newMat =  Matrix<T>(re - rs + 1, ce - cs + 1, 0);
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
            Matrix<T> newMat =  Matrix<T>(ce - cs + 1, re - rs + 1, 0);
            for(int i = 0; i < newMat._nRow; i++){
                for(int j = 0; j < newMat._nCol; j++){
                    // ...
                    newMat._data[i][j] = _data[i + cs][j + rs];
                }
            }
            return newMat;
        }
    }
    
    //...
    return Matrix<int>(1,1,0);
}

template<typename T>
std::vector<T> Matrix<T>::getRow(size_t r) const
{
    // get all element in r-row and push it back in a vector
    // remember check range first
    if((_t == 1 && r > _nRow) || (_t == 0 && r > _nCol)){
        throw range_error("getRow() :    Out Of Range");
    }
    vector<T> vec;
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

template<typename T>
std::vector<T> Matrix<T>::getCol(size_t c) const
{
    // get all element in c-column and push it back in a vector
    // remember check range first
    if((_t == 1 && c > _nCol) || (_t == 0 && c > _nRow)){
        throw range_error("getCol() :    Out Of Range");
    }
    vector<T> vec;
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

template<typename T>
bool Matrix<T>::setRow(size_t r, const vector<T>& d)
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

template<typename T>
bool Matrix<T>::setCol(size_t c, const vector<T>& d)
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

template<typename T>
Matrix<T>& Matrix<T>::transpose()
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

template<typename U>
ostream& operator<<(ostream& out, const Matrix<U>& rhs)
{
    for(size_t i = 0; i < rhs.getNRow(); ++i) {
        for(size_t j = 0; j < rhs.getNCol(); ++j) {
            out << rhs(i,j) << "\t";
        }
        out << endl;
    }
    return out;
}


#endif /* matrixTemplate_h */
