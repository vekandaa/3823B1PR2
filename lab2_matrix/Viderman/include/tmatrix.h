#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cassert>
#include <stdexcept>
#include <algorithm>

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz <= 0 || sz > MAX_VECTOR_SIZE)
            throw ("Недопустимый размер");
        pMem = new T[sz](); 
    }

    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        if (arr == nullptr || s <= 0) throw "некорректные данные";
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }

    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        for (int i = 0; i < sz; i++)
        {
            pMem[i] = v.pMem[i];
        }
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
    TDynamicVector& operator=(const TDynamicVector& v) {
        if (this == &v)
            return *this;
        TDynamicVector tmp(v);
        swap(*this, tmp);
        return *this;
    }

    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        swap(*this, v);
        return *this;
    }


    size_t size() const noexcept { return sz; }

    // Индексация
    T& operator[](size_t ind)
    {
        if (ind < 0 || ind > sz - 1) throw "некорректный индекс";
        return pMem[ind];
    }

    const T& operator[](size_t ind) const
    {
        return pMem[ind];
    }

    // Индексация с контролем
    T& at(size_t ind)
    {
        if (ind >= sz) throw std::out_of_range("Invalid index");
        return pMem[ind];
    }

    const T& at(size_t ind) const
    {
        if (ind >= sz) throw std::out_of_range("Invalid index");
        return pMem[ind];
    }

    // Сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) return false;
        for (size_t i = 0; i < sz; i++)
        {
            if (pMem[i] != v.pMem[i]) return false;
        }
        return true;
    }

    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    // Скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++)
            tmp.pMem[i] = pMem[i] + val;
        return tmp;
    }

    TDynamicVector operator-(T val) const
    {
        TDynamicVector res = *this;
        for (size_t i = 0; i < sz; i++)
        {
            res.pMem[i] -= val;
        }
        return res;
    }

    TDynamicVector operator*(T val) const
    {
        TDynamicVector res = *this;
        for (size_t i = 0; i < sz; i++)
        {
            res.pMem[i] *= val;
        }
        return res;
    }

    // Векторные операции
    TDynamicVector operator+(const TDynamicVector& v) const
    {
        if (sz != v.sz) throw std::invalid_argument("Vectors must be of the same length to add");
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++)
        {
            res.pMem[i] = pMem[i] + v.pMem[i];
        }
        return res;
    }

    TDynamicVector operator-(const TDynamicVector& v) const
    {
        if (sz != v.sz) throw std::invalid_argument("Vectors must be of the same length to subtract");
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++)
        {
            res.pMem[i] = pMem[i] - v.pMem[i];
        }
        return res;
    }

    T operator*(const TDynamicVector& v) const
    {
        if (sz != v.sz) throw std::invalid_argument("Vectors must be of the same length to multiply");
        T res = T();
        for (size_t i = 0; i < sz; i++)
        {
            res += pMem[i] * v.pMem[i];
        }
        return res;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // Ввод/вывод
    friend std::istream& operator>>(std::istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }

    friend std::ostream& operator<<(std::ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};

// Динамическая матрица
template<typename T>
class TDynamicMatrix : public TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (s <= 0 || s > MAX_MATRIX_SIZE) throw "Некорректный размер";
        //sz = s;
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(s); // Создаем квадратную матрицу
    }
    int get_size() { return sz; }
    using TDynamicVector<TDynamicVector<T>>::operator[];

    // Сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) return false;
        for (size_t i = 0; i < sz; i++)
        {
            if (pMem[i] != m.pMem[i]) return false; // Используем оператор== для векторов
        }
        return true;
    }

    // Матрично-скалярные операции
    TDynamicMatrix operator*(const T& val) const
    {
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++)
        {
            res.pMem[i] = pMem[i] * val; // Вызов векторного оператора
        }
        return res;
    }

    // Матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v) const
    {
        if (sz != v.size()) throw std::invalid_argument("Matrix columns must match vector size");
        TDynamicVector<T> res(sz);
        for (size_t i = 0; i < sz; i++)
        {
            res[i] = pMem[i] * v; // Используем векторный оператор
        }
        return res;
    }

    // Матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m) const
    {
        if (sz != m.sz) throw std::invalid_argument("Matrices must be of the same size to add");
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++)
        {
            res.pMem[i] = pMem[i] + m.pMem[i]; // Используем векторный оператор
        }
        return res;
    }

    TDynamicMatrix operator-(const TDynamicMatrix& m) const
    {
        if (sz != m.sz) throw std::invalid_argument("Matrices must be of the same size to subtract");
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++)
        {
            res.pMem[i] = pMem[i] - m.pMem[i]; // Используем векторный оператор
        }
        return res;
    }

    TDynamicMatrix operator*(const TDynamicMatrix& m) const
    {
        if (sz != m.sz) throw std::invalid_argument("Matrix sizes are incompatible for multiplication");
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++)
        {
            for (size_t j = 0; j < m.sz; j++)
            {
                res.pMem[i][j] = 0;
                for (size_t k = 0; k < sz; k++)
                {
                    res.pMem[i][j] += pMem[i][k] * m.pMem[k][j]; // Матричное умножение
                }
            }
        }
        return res;
    }

    // Ввод/вывод
    friend std::istream& operator>>(std::istream& istr, TDynamicMatrix& m)
    {
        for (size_t i = 0; i < m.sz; i++)
            istr >> m.pMem[i]; // Ввод каждой строки
        return istr;
    }

    friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix& m)
    {
        for (size_t i = 0; i < m.sz; i++)
            ostr << m.pMem[i] << std::endl; // Вывод каждой строки
        return ostr;
    }
};

#endif
