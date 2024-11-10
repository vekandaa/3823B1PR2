#include <iostream>
#include <vector>
#include "matrix.h"

using namespace std;


template<typename T>
class TSparceMatrixCOO
{
private:
    vector<T> NonZeroes;
    vector<T> IndRow;
    vector<T> IndCol;
    size_t nzsize;
public:
    TSparceMatrixCOO(const TDynamicMatrix<T>& m)
    {
        nzsize = 0;
        for (size_t i = 0; i < m.size(); i++) {
            for (size_t j = 0; j < m.size(); j++) {
                if (m[i][j] != 0) {
                    NonZeroes.push_back(m[i][j]);
                    IndRow.push_back(i);
                    IndCol.push_back(j);
                    nzsize++;
                }
            }
        }
    }
    TSparceMatrixCOO() : nzsize(0) {}

    TSparceMatrixCOO(const TSparceMatrixCOO& v)
    {
        NonZeroes = v.NonZeroes;
        IndRow = v.IndRow;
        IndCol = v.IndCol;
        nzsize = v.nzsize;
    }

    TSparceMatrixCOO& operator=(const TSparceMatrixCOO& v)
    {
        if (this != &v) {
            NonZeroes = v.NonZeroes;
            IndRow = v.IndRow;
            IndCol = v.IndCol;
            nzsize = v.nzsize;
        }
        return *this;
    }

    size_t size() const noexcept { return nzsize; }

    TSparceMatrixCOO operator*(const TSparceMatrixCOO& v)
    {
        if (IndCol.size() != v.IndRow.size()) {
            throw "Sizes are not compatible for multiplication";
        }
        TSparceMatrixCOO<T> tmp;

        for (size_t i = 0; i < nzsize; i++) {
            size_t row_1 = IndRow[i];
            size_t col_1 = IndCol[i];

            for (size_t j = 0; j < v.nzsize; j++) {
                size_t row_2 = v.IndRow[j];
                size_t col_2 = v.IndCol[j];

                if (col_1 == row_2) {
                    T elem = NonZeroes[i] * v.NonZeroes[j];
                    bool isFound = false;
                    for (size_t k = 0; k < tmp.nzsize; k++) {
                        if (row_1 == tmp.IndRow[k] && col_2 == tmp.IndCol[k]) {
                            tmp.NonZeroes[k] += elem;
                            isFound = true;
                            break;
                        }
                    }
                    if (!isFound) {
                        tmp.NonZeroes.push_back(elem);
                        tmp.IndRow.push_back(row_1);
                        tmp.IndCol.push_back(col_2);
                        tmp.nzsize++;
                    }
                    break;
                }
            }
        }
        return tmp;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TSparceMatrixCOO& v) {
        for (size_t i = 0; i < v.nzsize; i++) {
            istr >> v.NonZeroes[i] >> v.IndRow[i] >> v.IndCol[i];
        }
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TSparceMatrixCOO& v) {
        for (size_t i = 0; i < v.nzsize; i++) {
            ostr << v.NonZeroes[i] << ' ' << v.IndRow[i] << ' ' << v.IndCol[i] << endl;
        }
        return ostr;
    }
};
