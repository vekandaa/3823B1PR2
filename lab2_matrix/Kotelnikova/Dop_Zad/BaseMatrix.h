#include <iostream>
using namespace std;

#pragma once

class BaseMatrix {
private:
    int** data;
    int size;
public:
    BaseMatrix(int size) : size(size) {
        data = new int* [size];
        for (int i = 0; i < size; i++) {
            data[i] = new int[size];
            for (int j = 0; j < size; j++) {
                data[i][j] = 0;
            }
        }
    }

    ~BaseMatrix() {
        for (int i = 0; i < size; i++) {
            delete[] data[i];
        }
        delete[] data;
    }

    int* operator[](int index) { return data[index]; }

    const int* operator[](int index) const { return data[index]; }

    int getSize() const { return size; }

    int getValue(int i, int j) const { return data[i][j]; }

    BaseMatrix operator*(const BaseMatrix& m) {
        BaseMatrix res(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                res.data[i][j] = 0;
                for (int k = 0; k < size; k++) {
                    res.data[i][j] += data[i][k] * m.data[k][j];
                }
            }
        }
        return res;
    }

    void print() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }
};
