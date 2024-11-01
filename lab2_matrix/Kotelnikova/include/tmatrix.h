// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - шаблонный вектор на динамической памяти

template<typename T>
class TDynamicVector
{
protected:
  size_t sz;  // размерность вектора
  T* pMem;    // выделяем память под вектор
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
      if (sz == 0)
          throw out_of_range("Vector size should be greater than zero");
      if (sz > MAX_VECTOR_SIZE)
          throw out_of_range("Vector size exceeds maximum allowed size");
      pMem = new T[sz]();
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
      assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
      pMem = new T[sz];
      std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) : sz(v.sz)
  {
      pMem = new T[sz];
      for (size_t i = 0; i < sz; i++) {
          pMem[i] = v.pMem[i];
      }
  }
  TDynamicVector(TDynamicVector&& v) : sz(v.sz), pMem(v.pMem)
  {
      v.sz = 0;
      v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v) {
          if (sz != v.sz) {
              delete[] pMem;
              sz = v.sz;
              pMem = new T[sz];
          }
          for (size_t i = 0; i < sz; i++) {
              pMem[i] = v.pMem[i];
          }
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v)
  {
      if (this != &v) {
          delete[] pMem;
          sz = v.sz;
          pMem = v.pMem;
          v.sz = 0;
          v.pMem = nullptr;
      }
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
      if (ind >= sz)
          throw out_of_range("Index is out of range");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz)
          throw out_of_range("Index is out of range");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v)
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
  bool operator!=(const TDynamicVector& v)
  {
      if (sz != v.sz) {
          return true;
      }
      bool b = false;
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) {
              b = true;
          }
      }
      return b;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] + val;
      }
      return result;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] - val;
      }
      return result;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] * val;
      }
      return result;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw out_of_range("Vector size should be the same");
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] + v.pMem[i];
      }
      return result;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw out_of_range("Vector size should be the same");
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] - v.pMem[i];
      }
      return result;
  }
  T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
  {
      if (sz != v.sz)
          throw out_of_range("Vector size should be the same");
      T result = T();
      for (size_t i = 0; i < sz; i++) {
          result += pMem[i] * v.pMem[i];
      }
      return result;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) 
  {
      std::swap(lhs.sz, rhs.sz);
      std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
      for (size_t i = 0; i < v.sz; i++) {
          istr >> v.pMem[i];
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
      for (size_t i = 0; i < v.sz; i++) {
          ostr << v.pMem[i] << ' ';
      }
      return ostr;
  }
};


// Динамическая матрица - шаблонная матрица на динамической памяти

template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s > MAX_MATRIX_SIZE)
          throw out_of_range("Matrix size exceeds the maximum allowed size");

      for (size_t i = 0; i < sz; i++)
          pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  TDynamicVector<T>& operator[](size_t ind)
  {
      if (ind >= sz) {
          throw out_of_range("Row index out of range");
      }
      return pMem[ind];
  }
  const TDynamicVector<T>& operator[](size_t ind) const
  {
      if (ind >= sz) {
          throw out_of_range("Row index out of range");
      }
      return pMem[ind];
  }
  T& at(size_t row, size_t col)
  {
      if (row >= sz || col >= sz) {
          throw out_of_range("Index out of range");
      }
      return pMem[row][col];
  }
  const T& at(size_t row, size_t col) const
  {
      if (row >= sz || col >= sz) {
          throw out_of_range("Index out of range");
      }
      return pMem[row][col];
  }

  size_t size() const noexcept  { return sz; }

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
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
  TDynamicVector<T> operator*(const T& val)
  {
      TDynamicMatrix result(sz);
      for (size_t i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] * val;
      }
      return result;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.size())
          throw out_of_range("Not equal size");
      TDynamicVector<T> result(sz);
      for (size_t i = 0; i < sz; i++) {
          result[i] = pMem[i] * v;
      }
      return result;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw out_of_range("Not equal size");
      TDynamicMatrix result(sz);
      for (size_t i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] + m.pMem[i];
      }
      return result;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw out_of_range("Not equal size");
      TDynamicMatrix result(sz);
      for (size_t i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] - m.pMem[i];
      }
      return result;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw out_of_range("Not equal size");
      TDynamicMatrix result(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              result[i][j] = T();
              for (size_t k = 0; k < sz; k++) {
                  result[i][j] += pMem[i][k] * m.pMem[k][j];
              }
          }
      }
      return result;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t  i = 0; i < v.sz; i++) {
          istr >> v.pMem[i];
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t  i = 0; i < v.sz; i++) {
          ostr << v.pMem[i] << endl;
      }
      return ostr;
  }
};

#endif
