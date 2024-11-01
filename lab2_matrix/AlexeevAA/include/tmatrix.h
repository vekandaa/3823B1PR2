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
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    else if(sz > MAX_VECTOR_SIZE)
      throw out_of_range("Vector is so large");\
    else if(sz < 0)
      throw "Negative";

    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
    if(this == &v) throw "once memory";
    sz = v.sz;
    pMem = new T[sz];
    std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
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
    if(v.sz == sz){
      for(int i = 0; i < sz; i++) pMem[i] = v.pMem[i];
    }
    else{
      delete[] pMem;
      sz = v.sz;
      pMem = new T[v.sz];
      for(int i = 0; i < v.sz; i++) pMem[i] = v.pMem[i];
    }

    return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    swap(*this, v);
    return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      if(ind < 0) throw "negative";
      else if(ind >= sz) throw "out of range";

    return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
    if(ind < 0) throw "negative";
      else if(ind >= sz) throw "out of range";
    return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
    if(ind < 0) throw "negative";
      else if(ind >= sz) throw "out of range";
    return pMem[ind];
  }
  const T& at(size_t ind) const
  {
    if(ind < 0) throw "negative";
      else if(ind >= sz) throw "out of range";
    return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
    if(sz != v.sz) return false;
    else{
      for(int i = 0; i < sz; i++){
        if(pMem[i] != v.pMem[i]) return false;
      }
    }
    return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
    if(sz != v.sz) return true;
    else{
      for(int i = 0; i < sz; i++){
        if(pMem[i] != v.pMem[i]) return true;
      }
    }
    return false;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
    TDynamicVector<T> ans(*this);
    for(int i = 0; i < ans.sz; i++){
      ans.pMem[i] += val;
    }
    return ans;
  }
  TDynamicVector operator-(T val)
  {
    TDynamicVector<T> ans(*this);
    for(int i = 0; i < ans.sz; i++){
      ans.pMem[i] -= val;
    }
    return ans;
  }
  TDynamicVector operator*(T val)
  {
    TDynamicVector<T> ans(*this);
    for(int i = 0; i < ans.sz; i++){
      ans.pMem[i] *= val;
    }
    return ans;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if(sz != v.sz) throw "not equal sizes";
    TDynamicVector<T> k(*this);
    for(int i = 0; i < sz; i++){
      k.pMem[i] = pMem[i] + v.pMem[i];
    }
    return k;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
    if(sz != v.sz) throw "not equal sizes";
    TDynamicVector<T> k(*this);
    for(int i = 0; i < sz; i++){
      k.pMem[i] = pMem[i] + v.pMem[i];
    }
    return k;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
    if(sz != v.sz) throw "not equal sizes";
    T k = 0;
    for(int i = 0; i < sz; i++){
      k = k + pMem[i] * v.pMem[i];
    }
    return k;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
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
    if(sz > MAX_MATRIX_SIZE) throw "too large matrix";
    if(sz < 0) throw "negative size";

    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
    if(sz == m.sz){
      for(int i = 0; i < 0; i++){
        if(pMem[i] != m.pMem[i]) return false;
      }
    } else return false;
    return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix<T> operator*(const T& val)
  {
    TDynamicMatrix<T> ans(*this);
    for(int i = 0; i < sz; i++){
      ans.pMem[i] *= val;
    }
    return ans;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  { 
    std::cout;
    if(sz == v.sz){
      TDynamicVector<T> ans(v);
      for(int i = 0; i < sz; i++){
        ans[i] = pMem[i] * v;
      }
      return ans;
    }
    else throw -1;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
    if(sz == m.sz){
      TDynamicMatrix<T> ans(*this);
      for(int i = 0; i < sz; i++){
        ans.pMem[i] = pMem[i] + m.pMem[i];
      }
      return ans;
    }
    else throw -1;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    if(sz == m.sz){
      TDynamicMatrix<T> ans(*this);
      for(int i = 0; i < sz; i++){
        ans.pMem[i] = pMem[i] - m.pMem[i];
      }
      return ans;
    }
    else throw -1;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    if(sz == m.sz){
      TDynamicMatrix<T> ans(*this);
      for(int i = 0; i < sz;i++){
        for(int j = 0; j < sz;j++){
          int sum = 0;
          for(int k = 0; k < sz;k++){
            sum += pMem[i][k] * m.pMem[k][j];
          }
          ans[i][j] = sum;
        }
      }
    return ans;
    } else throw -1;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
    for(int i = 0; i < sz;i++){
      istr >> v.pMem[i];
    }
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
    for(int i = 0;i < v.sz;i++){
      ostr << v.pMem[i] << "\n";
    }
    return ostr;
  }
};

#endif
