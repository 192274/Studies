#include <iostream>
#include "Matrix.h"


int main() {
    Matrix m{2,2};
    m(0,0) = 1;
    m(0,1) = 2;
    m(1,0) = 3;
    m(1,1) = 4;
    Matrix m2{2, 1};
    m2(0, 0) = 2;
    m2(1, 0) = 1;
    std::cout << m * m2;
    return 0;
}