/*
The product of a matrix by a vector. In the resulting vector find the maximum element.
it is necessary to solve this problem by two ways:
• use only dynamic arrays with explicit dereferencing pointer
• use only dynamic arrays, addressing to elements array to perform using indexes.
*/

#include <cstdlib>
#include <iomanip>
#include <iostream>

#include "matrix.h"
#include "vector.h"

int main()
{
    // Matrix object
    Matrix3 m { 3, 3 };
    Vector v { 1, 2, 3 };
    // Initializes the matrix with random values
    m.IdentRand();
    m.MatrixPrint();

    v = v * m;
    v.Print();

    return 0;
}

// Declaration of the vector

// Calculates the product of the matrix by the vector

// Outputs the result of matrix by the vector
