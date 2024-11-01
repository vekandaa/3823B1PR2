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
  size_t sz; //размер выектора
  T* pMem; //ссылка на первый эл массива
public:
  TDynamicVector(size_t size = 1) : sz(size) //sz = size;
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s) //sz = s;
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg"); // проверка на нулптр
    pMem = new T[sz];//выделение динамической памяти по адресу pMem эл типа Т
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v){
      pMem = new T[v.sz];
      std::copy(v.arr, v.arr + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      pMem = v.pMem;
      sz(v.sz);
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
          delete[] pMem;
          sz = v.sz;
          pMem = new T[sz];
          std::copy(v.pMem, v.pMem + sz, pMem);
      }
      else {return *this}
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this != &v) {
          delete[] pMem;
          sz = v.sz;
          pMem = v.pMem;
          // Очищаем объект v
          v.sz = 0;
          v.pMem = nullptr;
      }
      else { return *this }
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      if (ind >= sz) {
          throw std::out_of_range("Index out of range");
      }
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      //if (ind >= sz) {
          //throw std::out_of_range("Index out of range");
      //}
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz) {
          throw std::out_of_range("Index out of range");
      }
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      //if (ind >= sz) {
          //throw std::out_of_range("Index out of range");
      //}
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept {
      if (sz != v.sz){return false}
      else {
          for (int i = 0; i < sz; i++) {
              if (pMem[i] != v.pMem[i]) {return false;}
          }
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept {
      if (sz != v.sz) {return true}
      else {
          for (int i = 0; i < sz; i++) {
              if (pMem[i] != v.pMem[i]) { return true; }
          }
      }
      return false;
  }

  // скалярные операции
  TDynamicVector operator+(T val) {
      TDynamicVector result(sz);

      for (int i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] + val;
      }
      return result;
  }
  TDynamicVector operator-(T val) {
      TDynamicVector result(sz);

      for (int i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] - val;
      }
      return result;
  }
  TDynamicVector operator*(T val) {
      TDynamicVector result(sz);

      for (int i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] * val;
      }
      return result;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v) {
      TDynamicVector result(sz);

      if (sz != v.sz) {
          throw std::out_of_range("Vectors must be of the same size for addition");
      }

      for (int i = 0; i < sz; i++) {
          result.pMem[i] = v.pMem[i] + pMem[i];
      }
      return result;
  }
  TDynamicVector operator-(const TDynamicVector& v) {
      TDynamicVector result(sz);

      if (sz != v.sz) {
          throw std::out_of_range("Vectors must be of the same size for addition");
      }

      for (int i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] - v.pMem[i];
      }
      return result;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T())) {
      if (sz != v.sz) {
          throw std::out_of_range("Vectors must be of the same size for dot product");
      }

      T result = T (); // спросить

      for (int i = 0; i < sz; i++) {
          result += pMem[i] * v.pMem[i];
      }
      return result;
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
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s) {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

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
  TDynamicVector<T> operator*(const T& val) {
      TDynamicVector<T> result(sz);

      for (int i = 0; i < sz; i++) {
          result[i] = pMem[i] * val;
      }
      return result;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v) {
      assert(sz == v.sz && "Vectors must have the same size for element-wise multiplication"); //почему именно это

      TDynamicVector<T> result(sz);
      for (int i = 0; i < sz; i++) {
          result[i] += pMem[i] * v.pMem[i];
      }
      return result;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m) {
      assert(sz == m.sz && "Matrices must have the same size for addition");

      TDynamicMatrix result(sz);  

      for (size_t i = 0; i < sz; i++) {
          result[i] = pMem[i] + m.pMem[i];
      }

      return result;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m) {
      assert(sz == m.sz && "Matrices must have the same size for addition");

      TDynamicMatrix result(sz);  // Создаем новую матрицу для результата

      for (size_t i = 0; i < sz; i++) {
          result[i] = pMem[i] - m.pMem[i];
      }

      return result;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m) {
      assert(sz == m.sz && "Matrix multiplication requires square matrices of the same size");

      TDynamicMatrix result(sz);

      for (size_t i = 0; i < sz; i++) {  // Для каждой строки первой матрицы
          for (size_t j = 0; j < sz; j++) {  // Для каждого столбца второй матрицы
              result[i][j] = 0;  // Инициализируем результат
              for (size_t k = 0; k < sz; k++) {  // Выполняем сумму произведений
                  result[i][j] += pMem[i][k] * m.pMem[k][j];
              }
          }
      }
      return result;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& m) {
      for (size_t i = 0; i < m.sz; i++) {
          for (size_t j = 0; j < m.sz; j++) {
              istr >> m.pMem[i][j];
          }
      }
      return istr;
  }

  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m) {
      for (size_t i = 0; i < m.sz; i++) {
          for (size_t j = 0; j < m.sz; j++) {
              ostr << m.pMem[i][j] << " ";
          }
          ostr << endl;
      }
      return ostr;
  }
};

#endif
