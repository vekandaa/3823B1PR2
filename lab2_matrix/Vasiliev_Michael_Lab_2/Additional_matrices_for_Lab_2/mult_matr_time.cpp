#include <iostream>
#include "sparce_matr.h"
#include <chrono>

using namespace std::chrono;

int main()
{
  auto start = high_resolution_clock::now();
  TDynamicMatrix<int> a(500), b(500), c(500);
  int i, j;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование класс работы с матрицами (coo)..."
    << endl;
  for (i = 0; i < 500; i++)
    for (j = 0; j < 500; j++ )
    {
      if (j % 5 == 0 && i % 10 == 0) {
        a[i][j] = i * 10 + j;
        b[i][j] = (i * 10 + j) * 100;
      }
    }
  
  TSparceMatrixCoo<int> a1(a), b1(b), c1(c);

  c1 = a1 * b1;

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);
  cout << duration.count() << endl;
}
