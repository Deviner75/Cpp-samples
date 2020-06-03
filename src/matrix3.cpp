#include "matrix3.h"
#include <iomanip>
#include <iostream>

Matrix3::Matrix3(int c, int r)
    : col(c)
    , row(r)
{
    p_mtx = new int*[col];
    for (int i = 0; i < row; i++) {
        p_mtx[i] = new int[row];
    }
}

Matrix3::~Matrix3()
{
    for (int i = 0; i < col; i++) {
        delete[] p_mtx[i];
    }
    delete[] p_mtx;
}

void Matrix3::IdentRand()
{
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            p_mtx[i][j] = rand() % 10 - 2;
        }
    }
}

void Matrix3::MatrixPrint()
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            std::cout << std::setw(2) << p_mtx[j][i] << " ";
        }
        std::cout << "\n";
    }
}

// Vector3 Matrix3::GetCol(int index) const
// {
//     Vector3 result;
//     result.x = p_mtx[index][0];
//     result.y = p_mtx[index][1];
//     result.z = p_mtx[index][2];

//     return result;
// }

// Vector3 Matrix3::GetRow(int index) const
// {
//     Vector3 result;
//     result.x = p_mtx[0][index];
//     result.x = p_mtx[1][index];
//     result.x = p_mtx[2][index];

//     return result;
// }
