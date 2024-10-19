#include <chrono>
#include "BaseMatrix.h"
#include "LineMatrix.h"
#include "SparseMatrix.h"
#include "CSR.h"

using namespace std::chrono;

int main()
{
    setlocale(LC_ALL, "Russian");

    int mtype;
    

    int size = 500;

    while (true) {
        cout << "Выберите тип матрицы ";
        cin >> mtype;

        switch (mtype)
        {
        case 1:
        {
            cout << "Base Matrix: " << endl;

            BaseMatrix m1(size), m2(size);
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (i % 5 == 0 && j % 5 == 0) {
                        m1[i][j] = i * 5 + j;
                        m2[i][j] = i * 5 + j;
                    }
                }
            }
            auto start = high_resolution_clock::now();
            BaseMatrix m3 = m1 * m2;
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start);
            cout << "Время умножения матриц: " << duration.count() << " миллисекунд" << endl;
            break;
        }
        case 2:
        {
            cout << "Line Matrix: " << endl;

            LineMatrix ma1(size), ma2(size);
            for (int i = 0; i < size; i++) {
                if (i % 5 == 0) {
                    ma1[i] = i * 5;
                    ma2[i] = i * 5;
                }
            }
            auto start = high_resolution_clock::now();
            LineMatrix ma3 = ma1 * ma2;
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start);
            cout << "Время умножения матриц: " << duration.count() << " миллисекунд" << endl;
            break;
        }
        case 3:
        {
            cout << "Sparse Matrix: " << endl;

            BaseMatrix m1(size), m2(size);
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (i % 10 == 0 && j % 5 == 0) {
                        m1[i][j] = i * 5 + j;
                        m2[i][j] = i * 5 + j;
                    }
                }
            }
            SparseMatrix mat1(m1), mat2(m2);
            auto start = high_resolution_clock::now();
            SparseMatrix mat3 = mat1 * mat2;
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start);
            cout << "Время умножения матриц: " << duration.count() << " миллисекунд" << endl;
            break;
        }
        case 4:
        {
            cout << "CSR Matrix: " << endl;

            BaseMatrix m1(size), m2(size);
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (j % 2 == 0 && i % 5 == 0) {
                        m1[i][j] = i * 5 + j;
                        m2[i][j] = (i * 5 + j) * 10;
                    }
                }
            }
            CSR matr1(m1), matr2(m2);
            auto start = high_resolution_clock::now();
            CSR matr3 = matr1 * matr2;
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start);
            cout << "Время умножения матриц: " << duration.count() << " миллисекунд" << endl;
            break;
        }
        default:
            cout << "Неверный выбор типа матрицы!" << endl;
            break;
        }
    }
}
