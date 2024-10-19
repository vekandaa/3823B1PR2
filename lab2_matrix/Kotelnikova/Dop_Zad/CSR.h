#include <iostream>
#include <vector>
using namespace std;

#pragma once

class CSR {
private:
    vector<int> NonZeroes;
    vector<int> IndCol;
    vector<int> IndRow;
    int size;
public:
    CSR(const BaseMatrix& m) {
        size = m.getSize();
        IndRow.push_back(0);

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                int value = m[i][j];
                if (value != 0) {
                    NonZeroes.push_back(value);
                    IndCol.push_back(j);
                }
            }
            IndRow.push_back(NonZeroes.size());
        }
    }

    CSR operator*(const CSR& other) {
        CSR result(size);
        result.IndRow.push_back(0);

        for (int i = 0; i < size; ++i) {
            vector<int> tempRow(size, 0);

            for (int j = IndRow[i]; j < IndRow[i + 1]; ++j) {
                int colA = IndCol[j];
                int valueA = NonZeroes[j];

                for (int k = other.IndRow[colA]; k < other.IndRow[colA + 1]; ++k) {
                    int colB = other.IndCol[k];
                    int valueB = other.NonZeroes[k];
                    tempRow[colB] += valueA * valueB;
                }
            }

            for (int col = 0; col < size; ++col) {
                if (tempRow[col] != 0) {
                    result.NonZeroes.push_back(tempRow[col]);
                    result.IndCol.push_back(col);
                }
            }
            result.IndRow.push_back(result.NonZeroes.size());
        }
        return result;
    }

    void print() const {
        for (int i = 0; i < size; ++i) {
            int currentIndex = IndRow[i];
            int nextIndex = IndRow[i + 1];
            for (int j = 0; j < size; ++j) {
                if (currentIndex < nextIndex && IndCol[currentIndex] == j) {
                    cout << NonZeroes[currentIndex] << " ";
                    ++currentIndex;
                }
                else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }
};

