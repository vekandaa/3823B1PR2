#ifndef __sparce_matr_csr_h__
#define __sparce_matr_csr_h__

#include <iostream>
#include "base_matrix.h"
#include <vector>

using namespace std;

template<typename T>
class TSparceMatrixCsr
{
private:
  vector<T> NonZeroes;
  vector<size_t> In_Row; // row_pointers
  vector<size_t> ColInd;
  size_t nzsize;  // nonzeroes_sizes
public:
  TSparceMatrixCsr(const TDynamicMatrix<T>& tmp)
  {
    nzsize = 0;
    In_Row.push_back(0);
    for (size_t i = 0; i < tmp.size(); i++) {
      for (size_t j = 0; j < tmp.size(); j++) {
        if (tmp[i][j] != 0) {
          NonZeroes.push_back(tmp[i][j]);
          ColInd.push_back(j);
          nzsize++;
        }
      }
      In_Row.push_back(nzsize);
    }
  }

  TSparceMatrixCsr(size_t _size) : nzsize(_size)
  {
    NonZeroes.resize(nzsize);
    In_Row.resize(nzsize / 2);
    ColInd.resize(nzsize);

  }

  TSparceMatrixCsr(const TSparceMatrixCsr& v) :  NonZeroes(v.NonZeroes), In_Row(v.In_Row), ColInd(v.ColInd), nzsize(v.nzsize)
  {
  }

  TSparceMatrixCsr& operator=(const TSparceMatrixCsr& v)
  {
    if (this != &v) {
      NonZeroes = v.NonZeroes;
      In_Row = v.In_Row;
      ColInd = v.ColInd;
      nzsize = v.nzsize;
    }

    return *this;
  }

  size_t size() const noexcept { return nzsize; }

  TSparceMatrixCsr operator*(const TSparceMatrixCsr& v)  // перемножение CSR матриц (техника через нахождение столба B матрицы, путем row_ptrs по индексу col_a)
  {
    if (nzsize != v.nzsize) {
      throw out_of_range("Sizes are not equal.");
    }
    TSparceMatrixCsr<T> tmp(1);
    size_t rows = In_Row.size() - 1;  // размер матрицы (тк в полях нет информации об этом)

    tmp.In_Row.push_back(0);
    vector<T> rowsres(rows);  // временное хранилище под i строку

    for (size_t i = 0; i < rows; i++) {
        fill(rowsres.begin(), rowsres.end(), 0); // зануляем при каждой новой строке

        for (size_t j = In_Row[i]; j < In_Row[i + 1]; j++) { // сколько всего non-zero элементов в строке matr A
            size_t col_a = ColInd[j];
            T value_a = NonZeroes[j];
        
            for (size_t k = v.In_Row[col_a]; k < v.In_Row[col_a + 1]; k++) { // сколько всего non-zero элементов столбца matr B
              size_t col_b = v.ColInd[k];
              T value_b = v.NonZeroes[k];

              rowsres[col_b] += value_a * value_b; // добавление элемента с индексом столба matr B
            }
        }

        for (size_t q = 0; q < rows; q++) {  // цикл для добавления в финальную CSR матрицу non-zeroes элементы из временного хранилища
          if (rowsres[q] != 0) {
            tmp.NonZeroes.push_back(rowsres[q]);
            tmp.ColInd.push_back(q);
            tmp.nzsize++;
          }
        }
        tmp.In_Row.push_back(tmp.nzsize);
    }
    return tmp;
  }
};

#endif
