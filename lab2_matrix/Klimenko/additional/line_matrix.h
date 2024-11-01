#include <iostream>
#include <math.h>
#include "matrix.h"

using namespace std;

template<typename T>
class TLineMatrix
{
protected:
    size_t sz;
    T* pMem;
public:
    TLineMatrix(size_t size = 1) : sz(size)
    {
        pMem = new T[sz * sz];
    }

    TLineMatrix(T* arr, size_t s) : sz(s)
    {
        pMem = new T[sz * sz];
        copy(arr, arr + sz, pMem);
    }

    TLineMatrix(TDynamicMatrix<T>& v) {
        sz = v.size();
        pMem = new T[sz * sz]();
        for (size_t i = 0; i < sz; i++)
            for (size_t j = 0; j < sz; j++)
                pMem[i * sz + j] = v[i][j];
    }

    TLineMatrix(const TLineMatrix& v) : sz(v.sz)
    {
        sz = v.sz;
        pMem = new T[sz * sz];
        for (int i = 0; i < sz; i++) {
            pMem[i] = v.pMem[i];
        }
    }

    TLineMatrix(TLineMatrix&& v) noexcept
    {
        sz = 0;
        pMem = nullptr;
        swap(*this, v);
    }

    ~TLineMatrix()
    {
        delete[] pMem;
    }

    TLineMatrix& operator=(const TLineMatrix& v)
    {
        if (this == &v) {
            return *this;
        }
        TLineMatrix tmp(v);
        swap(*this, tmp);
        return *this;
    }

    TLineMatrix& operator=(TLineMatrix&& v) noexcept
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


    TLineMatrix operator*(const TLineMatrix& v)
    {
        if (sz != v.sz) {
            throw "Sizes are not compatible for multiplication";
        }
        TLineMatrix<T> tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                for (size_t k = 0; k < sz; k++) {
                    tmp.pMem[(i * sz) + j] += pMem[(i * sz) + k] * v.pMem[(k * sz) + j];
                }
            }
        }
        return tmp;
    }

    friend void swap(TLineMatrix& lhs, TLineMatrix& rhs) 
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TLineMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++) {
            istr >> v.pMem[i];
        }
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TLineMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++) {
            ostr << v.pMem[i] << ' ';
        }
        return ostr;
    }
};
