#include <iostream>
#include "base_matrix.h"
#include <chrono>

using namespace std::chrono;
//---------------------------------------------------------------------------

int main()  // was void for some reason
{
  auto start = high_resolution_clock::now();
  TDynamicMatrix<int> a(500), b(500), c(500);
  int i, j;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование класс работы с матрицами (base)..."
    << endl;
  for (i = 0; i < 500; i++)
    for (j = 0; j < 500; j++ )
    {
      if (j % 5 == 0 && i % 10 == 0) {
        a[i][j] = i * 10 + j;
        b[i][j] = (i * 10 + j) * 100;
      }
    }

  c = a * b;

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);
  cout << duration.count() << endl;
}
//---------------------------------------------------------------------------
