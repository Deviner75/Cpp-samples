#pragma once
// Matrix class
// A matrix is arrays of numbers, arranged in rows and columns.
// Good for storing a stack of transformations and can transform points efficiently.

// Creates matrix data type
struct Matrix3 {
    int col { 1 }, row { 1 };
    int** p_mtx = nullptr;

    // Default constructor
    Matrix3() {};
    // Creates an array of pointers to columns and rows
    Matrix3(int c, int r);
    // Destructor
    ~Matrix3();
    // Idents the matrix with random values
    void IdentRand();
    // Prints out the matrix's values
    void MatrixPrint();
    //     // Returns one of the columns of a matrix
    //     Vector3 GetCol(int index) const;
    //     // Returns one of the rows of a matrix
    //     Vector3 GetRow(int index) const;
};