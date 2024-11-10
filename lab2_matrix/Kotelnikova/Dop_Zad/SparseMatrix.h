#include <iostream>
#include <vector>
using namespace std;

#pragma once

class SparseMatrix {
private:
    vector<int> NonZeroes;
    vector<int> IndRow;
    vector<int> IndCol;
    int size;
public:
    SparseMatrix(const BaseMatrix& m) {
        size = m.getSize();
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                int value = m.getValue(i, j);
                if (value != 0) {
                    NonZeroes.push_back(value);
                    IndRow.push_back(i);
                    IndCol.push_back(j);
                }
            }
        }
    }

    SparseMatrix operator*(const SparseMatrix& m) {
        SparseMatrix result(size);

        for (int i = 0; i < NonZeroes.size(); ++i) {
            int rowA = IndRow[i];
            int colA = IndCol[i];
            int valueA = NonZeroes[i];

            for (int j = 0; j < m.NonZeroes.size(); ++j) {
                int rowB = m.IndRow[j];
                int colB = m.IndCol[j];
                int valueB = m.NonZeroes[j];

                if (colA == rowB) {
                    int row = rowA;
                    int col = colB;
                    int value = valueA * valueB;

                    bool found = false;
                    for (int k = 0; k < result.NonZeroes.size(); ++k) {
                        if (result.IndRow[k] == row && result.IndCol[k] == col) {
                            result.NonZeroes[k] += value;
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        result.NonZeroes.push_back(value);
                        result.IndRow.push_back(row);
                        result.IndCol.push_back(col);
                    }
                }
            }
        }
        return result;
    }

    void print() const {
        vector<vector<int>> fullMatrix(size, vector<int>(size, 0));
        for (int i = 0; i < NonZeroes.size(); ++i) {
            fullMatrix[IndRow[i]][IndCol[i]] = NonZeroes[i];
        }
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << fullMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

