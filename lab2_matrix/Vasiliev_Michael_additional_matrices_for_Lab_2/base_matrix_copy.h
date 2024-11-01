#ifndef __base_matrix_copy_h__
#define __base_matrix_copy_h__

#include <iostream>
#include <math.h>

using namespace std;

template<typename T>
class TMatrixVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TMatrixVector(size_t size = 1) : sz(size)
  {
    pMem = new T[sz]();
  }

  TMatrixVector(T* arr, size_t s) : sz(s)
  {
    pMem = new T[sz];
    copy(arr, arr + sz, pMem);
  }
  
  TMatrixVector(const TMatrixVector& v) : sz(v.sz)
  {
    pMem = new T[sz];
    copy(v.pMem, v.pMem + sz, pMem);
  }

  TMatrixVector(TMatrixVector&& v) //noexcept
  {
    pMem = nullptr;
    swap(*this, v);
  }

  ~TMatrixVector()
  {
    delete[] pMem;
  }
  
  TMatrixVector& operator=(const TMatrixVector& v)
  {
    if (this == &v) {
      return *this;
    }
    TMatrixVector tmp(v);
    swap(*this, tmp);
    return *this;
  }
  
  TMatrixVector& operator=(TMatrixVector&& v) //noexcept
  {
    swap(*this, v);
    return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
    return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
    return pMem[ind];
  }

 
  TMatrixVector operator*(const TMatrixVector& v) // noexcept(noexcept(T()))
  {
    if (sz != v.sz) {
      throw out_of_range("Sizes are not equal.");
    }
    TMatrixVector<T> tmp(sz);
    int rcsize = sqrt(sz);
    for (size_t i = 0; i < rcsize; i++) {
      for (size_t j = 0; j < rcsize; j++) {
        tmp.pMem[(i * rcsize) + j] = 0;
        for (size_t k = 0; k < rcsize; k++) {
          tmp.pMem[(i * rcsize) + j] += pMem[(i * rcsize) + k] * v.pMem[(k * rcsize) + j];
        }  
      }
    }
    return tmp;
  }

  friend void swap(TMatrixVector& lhs, TMatrixVector& rhs) //noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TMatrixVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i];
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TMatrixVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' ';
    return ostr;
  }
};

#endif
