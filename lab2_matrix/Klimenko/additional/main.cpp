#include <iostream>
#include <chrono>
#include "line_matrix.h"
#include "coo.h"
#include "matrix.h"


using namespace std::chrono;


int main() 
{
    size_t size = 700;
    setlocale(LC_ALL, "Russian");

    // MATRIX TO MATRIX 

    auto start = high_resolution_clock::now();
    TDynamicMatrix<int> matrix1(size), matrix2(size), matrixres(size);
    
    cout << "Matrice to matrice: " << endl;
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            if (i % 5 == 0 && j % 10 == 0) {
                matrix1[i][j] = i * 5 + j;
                matrix2[i][j] = (i * 5 + j) * 10;
            }
        }
    }

    matrixres = matrix1 * matrix2;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << duration.count() << " ms " << endl;

    // LINE TO LINE

    auto start1 = high_resolution_clock::now();
    TLineMatrix<int> matrix_1(matrix1), matrix_2(matrix2), matrix_res(matrixres); 
    
    cout << "Line to line: " << endl;

    matrix_res = matrix_1 * matrix_2;
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(stop1 - start1);
    cout << duration1.count() << " ms " << endl;

    // COO

    auto start2 = high_resolution_clock::now();
    TDynamicMatrix<int> temp_matrice1(matrix1), temp_matrice2(matrix2), temp_matrice3(matrixres);

    cout << "COO: " << endl;

    TSparceMatrixCOO<int> matrice1(temp_matrice1), matrice2(temp_matrice2), matrice_res(temp_matrice3);

    matrice_res = matrice1 * matrice2;
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(stop2 - start2);
    cout << duration2.count() << " ms " << endl;
}
