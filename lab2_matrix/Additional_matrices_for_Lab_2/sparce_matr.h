#ifndef __sparce_matr_h__
#define __sparce_matr_h__

#include <iostream>
#include "base_matrix.h"
#include <vector>

using namespace std;

template<typename T>
class TSparceMatrixCoo
{
private:
  vector<T> NonZeroes;
  vector<size_t> RowInd;
  vector<size_t> ColInd;
  size_t nzsize;
public:
  TSparceMatrixCoo(const TDynamicMatrix<T>& tmp)
  {
    nzsize = 0;
    for (size_t i = 0; i < tmp.size(); i++) {
      for (size_t j = 0; j < tmp.size(); j++) {
        if (tmp[i][j] != 0) {
          NonZeroes.push_back(tmp[i][j]);
          RowInd.push_back(i);
          ColInd.push_back(j);
          nzsize++;
        }
      }
    }
  }

  TSparceMatrixCoo(size_t _size) : nzsize(_size)
  {
    NonZeroes.resize(nzsize);
    RowInd.resize(nzsize);
    ColInd.resize(nzsize);

  }

  TSparceMatrixCoo(const TSparceMatrixCoo& v) :  NonZeroes(v.NonZeroes), RowInd(v.RowInd), ColInd(v.ColInd), nzsize(v.nzsize)
  {
  }

  TSparceMatrixCoo& operator=(const TSparceMatrixCoo& v)
  {
    if (this != &v) {
      NonZeroes = v.NonZeroes;
      RowInd = v.RowInd;
      ColInd = v.ColInd;
      nzsize = v.nzsize;
    }

    return *this;
  }

  size_t size() const noexcept { return nzsize; }

  TSparceMatrixCoo operator*(const TSparceMatrixCoo& v)
  {
    if (nzsize != v.nzsize) {
      throw out_of_range("Sizes are not equal.");
    }
    TSparceMatrixCoo<T> tmp(1);

    for (int i = 0; i < nzsize; i++) {
        size_t row_a = RowInd[i];
        size_t col_a = ColInd[i];

        for (int j = 0; j < v.nzsize; j++) {
            size_t row_b = v.RowInd[j];
            size_t col_b = v.ColInd[j];
        
            if (col_a == row_b) {
                int trg = 0;
                T elem = NonZeroes[i] * v.NonZeroes[j];
                for (int k = 0; k < tmp.nzsize; k++) {
                  if (row_a == tmp.RowInd[k] && col_b == tmp.ColInd[k]) {
                    tmp.NonZeroes[k] += elem;
                    trg = 1;
                    break;
                  }
                }
                if (trg == 0) {
                  tmp.NonZeroes.push_back(elem);
                  tmp.RowInd.push_back(row_a);
                  tmp.ColInd.push_back(col_b);
                  tmp.nzsize++;
                }
              break;
            }
        }
    }
    return tmp;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TSparceMatrixCoo& v)
  {
    for (size_t i = 0; i < v.nzsize; i++)
      istr >> v.NonZeroes[i] >> v.RowInd[i] >> v.ColInd[i];
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TSparceMatrixCoo& v)
  {
    for (size_t i = 0; i < v.nzsize; i++)
      ostr << v.NonZeroes[i] << ' ' << v.RowInd[i] << ' ' << v.ColInd[i] << endl;
    return ostr;
  }
};

#endif
