//
// Created by w on 3/30/18.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <vector>
#include <ostream>


class Matrix {

public:

    Matrix() ;
    Matrix(int m, int n) ;

    double & operator()(int m, int n) ;
    double operator()(int m, int n) const ;

    friend Matrix operator+(const Matrix & lhv, const Matrix & rhv) ;
    friend Matrix operator+(const Matrix & lhv, double rhv) ;
    friend Matrix operator+(double lhv, const Matrix & rhv) ;
    friend Matrix operator-(const Matrix & lhv, const Matrix & rhv) ;
    friend Matrix operator-(const Matrix & lhv, double rhv) ;
//    friend Matrix operator*(const Matrix & lhv, const Matrix & rhv) const;
    friend Matrix operator*(const Matrix & lhv, double rhv) ;
    friend Matrix operator*(double rhv, const Matrix & lhv) ;
    friend Matrix operator/(const Matrix & lhv, double rhv) ;
//    friend Matrix operator^(const Matrix & lhv, int rhv) const;
    bool operator==(const Matrix & rhv) const;
    Matrix & operator=(const Matrix & rhv) ;
    Matrix & operator+=(const Matrix & rhv);
    Matrix & operator-=(const Matrix & rhv);
    Matrix & operator-=(double rhv);
    Matrix & operator*=(const Matrix & rhv);
    Matrix & operator*=(double rhv);
    Matrix & operator/=(double rhv);
//    Matrix & invert() const;

    int verses() const {
        return m;
    };

    int columns() const {
        return n;
    };


private:

    int m ;
    int n ;
    std::vector<std::vector<double>> v ;
    bool outOfRange(int m, int n) const ;
};

std::ostream & operator<<(std::ostream & os, const Matrix & matrix) ;


#endif //MATRIX_MATRIX_H
