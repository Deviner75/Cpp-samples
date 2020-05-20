/*
2. Given an integer rectangular matrix. Define:
a) the number of columns that do not contain a single zero element;
the characteristic of a column of an integer matrix is the sum of the moduli of its negative even elements.
b) Rearranging the columns of a given matrix, arrange them in accordance with the growth of characteristics.
Merge sort algorithm was used
*/

#include <cstdlib>
#include <iomanip>
#include <iostream>

// Matrixes columns X rows
#define COL 10
#define ROW 5

// Merge Sort
void MergeSort(int* arr, int low, int high, int** mtx);
void Merge(int* arr, int low, int high, int mid, int** mtx);

void MatrixPrint(int** mtx);

int main()
{
    // A Table of pointers for each matrix row
    int** matrix = new int*[COL];

    // Variables
    int sum = 0, countNull = 0;
    int sumcol[COL];

    // Rows initialization
    std::cout << "Matrix : " << std::endl;
    for (int i = 0; i < COL; i++) {
        matrix[i] = new int[ROW];
    }
    // Matrix initialization with random values
    for (int i = 0; i < COL; i++) {
        for (int j = 0; j < ROW; j++) {
            matrix[i][j] = rand() % 10 - 2;
        }
    }
    MatrixPrint(matrix);
    std::cout << "a)----------Columns do not contain 0s----------" << std::endl;
    // Counts the number of columns that do not contain a single zero element
    for (int i = 0; i < COL; i++) {
        countNull = 0;
        for (int j = 0; j < ROW; j++) {
            if (matrix[i][j] != 0) {
                countNull++;
            }
        }
        if (countNull == ROW)
            std::cout << "Column " << i + 1 << std::endl;
    }

    std::cout << "b)----------Sorted Matrix----------" << std::endl;
    // Counts the number of columns that do not contain a single zero element
    std::cout << "Characteristics: \n";
    for (int i = 0; i < COL; i++) {
        sum = 0;
        for (int j = 0; j < ROW; j++) {
            if ((matrix[i][j] < 0) && (matrix[i][j] % 2 != 0)) {
                sum += abs(matrix[i][j]);
            }
        }
        sumcol[i] = sum;
        std::cout << sum << " ";
    }

    std::cout << "\n"
              << "Characteristics sorted: \n";
    // Sorts the number of columns that do not contain a single zero element
    MergeSort(sumcol, 0, COL - 1, matrix);
    for (int i = 0; i < COL; i++) {
        std::cout << sumcol[i] << " ";
    }

    std::cout << "\n"
              << "Matrix Sorted: \n";
    MatrixPrint(matrix);

    // Clean up
    for (int i = 0; i < COL; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 1;
}

// Merge sort
void MergeSort(int* arr, int low, int high, int** mtx)
{
    int mid;
    if (low < high) {
        //divide the array at mid and sort independently using merge sort
        mid = (low + high) / 2;
        MergeSort(arr, low, mid, mtx);
        MergeSort(arr, mid + 1, high, mtx);
        //merge or conquer sorted arrays
        Merge(arr, low, high, mid, mtx);
    }
}

void Merge(int* arr, int low, int high, int mid, int** mtx)
{
    int i, j, k, c[high + 1];
    int* mtx2[high + 1];
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high) {
        if (arr[i] < arr[j]) {
            c[k] = arr[i];
            mtx2[k] = mtx[i];
            k++;
            i++;
        } else {
            c[k] = arr[j];
            mtx2[k] = mtx[j];
            k++;
            j++;
        }
    }
    while (i <= mid) {
        c[k] = arr[i];
        mtx2[k] = mtx[i];
        k++;
        i++;
    }
    while (j <= high) {
        c[k] = arr[j];
        mtx2[k] = mtx[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++) {
        arr[i] = c[i];
        mtx[i] = mtx2[i];
    }
}

void MatrixPrint(int** mtx)
{
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            std::cout << std::setw(2) << mtx[j][i] << " ";
        }
        std::cout << "\n";
    }
}