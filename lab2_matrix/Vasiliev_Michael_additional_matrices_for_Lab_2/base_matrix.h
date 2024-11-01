// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __base_matrix_h__
#define __base_matrix_h__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0 || sz > MAX_VECTOR_SIZE)
      throw out_of_range("Vector size should be greater than zero and less than 10^8");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector requires non-nullptr arg");
    pMem = new T[sz];
    copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) : sz(v.sz)
  {
    pMem = new T[sz];
    copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) //noexcept
  {
    pMem = nullptr;
    swap(*this, v);
  }
  ~TDynamicVector()
  {
    delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if (this == &v) {
      return *this;
    }
    TDynamicVector tmp(v);
    swap(*this, tmp);
    return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) //noexcept
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
  // индексация с контролем
  T& at(size_t ind)
  {
    if (ind >= sz) {
      throw out_of_range("index more or equal than size");
    }
    return pMem[ind];
  }
  const T& at(size_t ind) const
  {
    if (ind >= sz) {
      throw out_of_range("index more or equal than size");
    }
    return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const //noexcept
  {
    if (sz != v.sz) {
      return false;
    }

    for (size_t i = 0; i < sz; i++) {
      if (pMem[i] != v.pMem[i]) {
        return false;
      }
    }

    return true;
  }
  bool operator!=(const TDynamicVector& v) const //noexcept
  {
    if (sz != v.sz) {
      return true;
    }

    for (size_t i = 0; i < sz; i++) {
      if (pMem[i] != v.pMem[i]) {
        return true;
      }
    }
    
    return false;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
    TDynamicVector tmp(sz);
    for (size_t i = 0; i < sz; i++) {
      tmp.pMem[i] = pMem[i] + val;
    }
    return tmp;
  }
  TDynamicVector operator-(T val)
  {
    TDynamicVector tmp(sz);
    for (size_t i = 0; i < sz; i++) {
      tmp.pMem[i] = pMem[i] - val;
    }
    return tmp;
  }
  TDynamicVector operator*(T val)
  {
    TDynamicVector tmp(sz);
    for (size_t i = 0; i < sz; i++) {
      tmp.pMem[i] = pMem[i] * val;
    }
    return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if (sz != v.sz) {
      throw out_of_range("Sizes are not equal.");
    }
    TDynamicVector tmp(sz);
    for (size_t i = 0; i < sz; i++) {
      tmp.pMem[i] = pMem[i] + v.pMem[i];
    }
    return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
    if (sz != v.sz) {
      throw out_of_range("Sizes are not equal.");
    }
    TDynamicVector tmp(sz);
    for (size_t i = 0; i < sz; i++) {
      tmp.pMem[i] = pMem[i] - v.pMem[i];
    }
    return tmp;
  }
  T operator*(const TDynamicVector& v) // noexcept(noexcept(T()))
  {
    if (sz != v.sz) {
      throw out_of_range("Sizes are not equal.");
    }
    T tmp_res = 0;
    T res = 0;
    for (size_t i = 0; i < sz; i++) {
      tmp_res = pMem[i] * v.pMem[i];
      res += tmp_res;
    }
    return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) //noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i];
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' ';
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (s == 0 || s > MAX_MATRIX_SIZE)
      throw out_of_range("Matrix size should be greater than zero and less than 10^4");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::size; // for get size of square matrix

  using TDynamicVector<TDynamicVector<T>>::operator[];

  using TDynamicVector<TDynamicVector<T>>::at;

  // сравнение
  bool operator==(const TDynamicMatrix& m) const //noexcept
  {
    if (sz != m.sz) {
      return false;
    }

    for (size_t i = 0; i < sz; i++) {
      if (pMem[i] != m.pMem[i]) {
        return false;
      }
    }

    return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix<T> operator*(const T& val)  // TDynamicVector<T>??
  {
    TDynamicMatrix<T> tmp(sz);
    for (size_t i = 0; i < sz; i++) {
      for (size_t j = 0; j < sz; j++) {
        tmp.pMem[i][j] = pMem[i][j] * val;
      }
    }
    return tmp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
    if (sz != v.size()) {
      throw out_of_range("Sizes are not equal.");
    }
    TDynamicVector<T> tmp(sz);

    for (size_t i = 0; i < sz; i++) {
      tmp[i] = 0;
  
      for (size_t j = 0; j < sz; j++) {
        tmp[i] += pMem[i][j] * v[j];
      }
    }

    return tmp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
    if (sz != m.sz) {
      throw out_of_range("Sizes are not equal.");
    }
    TDynamicMatrix<T> tmp(sz);
    for (size_t i = 0; i < sz; i++) {
      for (size_t j = 0; j < sz; j++) {
        tmp.pMem[i][j] = pMem[i][j] + m.pMem[i][j];
      }
    }
    return tmp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    if (sz != m.sz) {
      throw out_of_range("Sizes are not equal.");
    }
    TDynamicMatrix<T> tmp(sz);
    for (size_t i = 0; i < sz; i++) {
      for (size_t j = 0; j < sz; j++) {
        tmp.pMem[i][j] = pMem[i][j] - m.pMem[i][j];
      }
    }
    return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    if (sz != m.sz) {
      throw out_of_range("Sizes are not equal.");
    }
    TDynamicMatrix<T> tmp(sz);
    for (size_t i = 0; i < sz; i++) {
      for (size_t j = 0; j < sz; j++) {
        tmp.pMem[i][j] = 0;
        for (size_t k = 0; k < sz; k++) {
          tmp.pMem[i][j] += pMem[i][k] * m.pMem[k][j]; // 00 - 00*00 + 01*10 || 01 - 00*01 + 01*11 || 10 - 10*00 + 11*10 || 11 - 10*01 + 11*11;
        }  
      }
    }
    return tmp;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz; i++) {
      for (size_t j = 0; j < v.sz; j++) {
        istr >> v.pMem[i][j];
      }
    }

    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
    int k = 0;
    for (size_t i = 0; i < v.sz; i++) {
      ostr << "[ ";
      for (size_t j = 0; j < v.sz - 1; j++) {
        ostr << v.pMem[i][j] << ' ';
        k = j;
      }
      ostr << v.pMem[i][k+1] << " ]" << endl;
    }

    return ostr;
  }
};

#endif
