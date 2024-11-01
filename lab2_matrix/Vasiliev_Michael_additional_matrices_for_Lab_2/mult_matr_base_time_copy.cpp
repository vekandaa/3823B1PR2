#include <iostream>
#include "base_matrix_copy.h"
#include <chrono>
#include <math.h>

using namespace std::chrono;
//---------------------------------------------------------------------------

int main()  // was void for some reason
{
  auto start = high_resolution_clock::now();
  TMatrixVector<int> a(250000), b(250000), c(250000);  // n * n = size;
  int i, j;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование класс работы с матрицами (one vector)..."
    << endl;
  for (i = 0; i < 500; i++)
    for (j = 0; j < 500; j++ )
    {
      if (j % 5 == 0 && i % 10 == 0) {
        a[(i * 500) + j] = i * 10 + j;
        b[(i * 500) + j] = (i * 10 + j) * 100;
      }
    }

  c = a * b;

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);
  cout << duration.count() << endl;
}
//---------------------------------------------------------------------------
