#include <iostream>
using namespace std;

#pragma once

class LineMatrix {
private:
    int* data;
    int size;

public:
    LineMatrix(int size) : size(size) {
        data = new int[size * size];
        for (int i = 0; i < size * size; i++) {
            data[i] = 0;
        }
    }

    ~LineMatrix() { delete[] data; }

    int& operator[](int index) { return data[index]; }

    const int& operator[](int index) const { return data[index]; }

    LineMatrix operator*(const LineMatrix& m) {
        LineMatrix res(size);
        for (int i = 0; i < size * size; i++) {
            res.data[i] = 0;
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                for (int k = 0; k < size; k++) {
                    res.data[i * size + j] += data[i * size + k] * m.data[k * size + j];
                }
            }
        }
        return res;
    }

    void print() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << data[i * size + j] << " ";
            }
        }
        cout << endl;
    }
};
