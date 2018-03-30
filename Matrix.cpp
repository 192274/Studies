//
// Created by w on 3/30/18.
//

#include <stdexcept>
#include "Matrix.h"

Matrix::Matrix() : m{0}, n{0}, v{0} {

}

Matrix::Matrix(int m, int n) : m {m}, n{n}, v{m} {
    for(int i = 0; i < m; ++i)
        v[i].resize(n);
}

double & Matrix::operator()(int m, int n) {
    if(outOfRange(m, n))
        throw std::out_of_range{"Matrix coordinates out of range"};
    return v[m][n];
}

double Matrix::operator()(int m, int n) const {
    if(outOfRange(m, n))
        throw std::out_of_range{"Matrix coordinates out of range"};
    return v[m][n];
}

Matrix operator+(const Matrix & lhv, const Matrix & rhv) {
    if(lhv.m != rhv.m || lhv.n != rhv.n)
        throw std::runtime_error("Incompatibile dimensions");
    Matrix sum(lhv.m, lhv.n);
    for(int i = 0; i <= lhv.m; i++)
        for(int j = 0; j <= lhv.n; j++)
            sum(i, j) = lhv(i, j) + rhv(i, j);
}

Matrix operator+(const Matrix & lhv, double rhv) {
    Matrix sum{lhv.verses(), lhv.columns()};
    for(int i = 0; i < lhv.verses(); ++i)
        for(int j = 0; j < lhv.columns(); ++j)
            sum(i, j) = lhv(i,j) + rhv;
    return sum;
}

Matrix operator+(double rhv, const Matrix & lhv) {
    return lhv + rhv;
}

Matrix operator-(const Matrix & lhv, const Matrix & rhv) {
    return lhv + (rhv * -1);
}

Matrix operator-(const Matrix & lhv, double rhv) {
    return lhv + (-rhv);
}

Matrix operator*(const Matrix & lhv, const Matrix & rhv) {
    Matrix product{};
}

Matrix operator*(const Matrix & lhv, double rhv) {
    Matrix product{lhv.verses(), lhv.columns()};
    for(int i = 0; i < lhv.verses(); ++i)
        for(int j = 0; j < lhv.columns(); ++j)
            product(i, j) = lhv(i, j) * rhv;
    return product;
}

Matrix operator*(double lhv, const Matrix & rhv) {
    return rhv * lhv;
}

Matrix operator/(const Matrix & lhv, double rhv) {
    Matrix product{lhv.verses(), lhv.columns()};
    for(int i = 0; i < lhv.m; ++i)
        for(int j = 0; j < lhv.n; ++j)
            product(i, j) = lhv(i, j) / rhv;
    return product;
}

//Matrix operator^(const Matrix & lhv, int rhv) const;

bool Matrix::operator==(const Matrix & rhv) const {
    if(rhv.m != m || rhv.n != n)
        return false;
    for(int i = 0; i < m; ++i)
        for(int j = 0; j < n; ++j)
            if((*this)(i, j) != rhv(i, j))
                return false;
    return true;
}

Matrix & Matrix::operator=(const Matrix & rhv) {
    m = rhv.m;
    n = rhv.n;
    v.resize(m);
    for(int i = 0; i < m; ++i) {
        v[i].resize(n);
        for (int j = 0; j < n; ++j)
            v[i][j] = rhv.v[i][j];
    }
    return *this;
}

Matrix & Matrix::operator+=(const Matrix & rhv) {
    *this = *this + rhv;
}

Matrix & Matrix::operator-=(const Matrix & rhv) {
    return *this = *this - rhv;
}

Matrix & Matrix::operator-=(double rhv) {
    return *this = *this - rhv;
}

Matrix & Matrix::operator*=(const Matrix & rhv) {
    return *this = *this * rhv;
}

Matrix & Matrix::operator*=(double rhv) {
    return *this = *this * rhv;
}

Matrix & Matrix::operator/=(double rhv) {
    return *this = *this / rhv;
}

//Matrix & Matrix::invert() const;

bool Matrix::outOfRange(int m, int n) const {
    if(m < 0 || m >= this->m || n < 0 || n >= this->n)
        return true;
    return false;
}

std::ostream & operator<<(std::ostream & os, const Matrix & matrix) {
    for(int i = 0; i < matrix.verses(); ++i) {
        for (int j = 0; j < matrix.columns(); ++j) {
            os << matrix(i, j) << ' ';
        }
        os << '\n';
    }
    return os;
}
