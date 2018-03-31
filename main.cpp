#include <iostream>
#include "Matrix.h"


int main() {
    Matrix m{3,2};
    m(0,0) = 1;
    m(0,1) = 2;
    m(1,0) = 3;
    m(1,1) = 4;
    Matrix m2{5, 6};
    std::cout << m2;
    std::cout << std::endl << m ;
    std::cout << std::endl << (m2 = m) << std::endl;
    return 0;
}