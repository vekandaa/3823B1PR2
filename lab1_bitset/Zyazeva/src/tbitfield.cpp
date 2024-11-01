// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле


#include "tbitfield.h"
#include <stdexcept>
const int SIZE = sizeof(TELEM)*8;

//bitlen/telem - 1
// Конструктор
TBitField::TBitField(int len) {
    if (len < 0) {
        throw string("out of range");
    }
    BitLen = len;
    MemLen = len / SIZE +1;
    pMem = new TELEM[MemLen]; 
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField& bf) {
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}


TBitField::~TBitField() {
    delete[] pMem;
}


int TBitField::GetMemIndex(const int n) const {
    return n/ SIZE;
}


TELEM TBitField::GetMemMask(const int n) const {

    return (TELEM)1 << (n%SIZE);
}


int TBitField::GetLength() const {
    return BitLen;
}


void TBitField::SetBit(const int n) {
    if ((n < 0)||(n >= BitLen)) {
        throw string("out of range");
    }
    pMem[GetMemIndex(n)] |= (unsigned int)GetMemMask(n);

}

void TBitField::ClrBit(const int n) {
    if ((n < 0) || (n >= BitLen)) {
        throw string("out of range");
    }
    pMem[GetMemIndex(n)] &= (unsigned int)~GetMemMask(n);
}


int TBitField::GetBit(const int n) const {
    if ((n < 0) || (n >= BitLen)) {
        throw string("out of range");
    }
    return (unsigned int)((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0);
}


TBitField& TBitField::operator=(const TBitField& bf) {
    if (this != &bf) { 
         
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        delete[] pMem;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField& bf) const {
    for (int u = 0; u < MemLen; u++) {
        if (pMem[u] != bf.pMem[u]) return 0;
    }
    return 1;
}

int TBitField::operator!=(const TBitField& bf) const {
    if (BitLen != bf.BitLen) return 1; 
    for (int u = 0; u < BitLen; u++) {
        if (pMem[u] != bf.pMem[u]) return 1; 
    }
    return 0;
    if (BitLen != bf.BitLen) return 0;
}

TBitField TBitField::operator|(const TBitField& bf) { 
    int maxLen;
    if (BitLen > bf.BitLen) {
        maxLen = BitLen;
    }
    else {
        maxLen = bf.BitLen;
    }
    TBitField res(maxLen);
    for (int u = 0; u < (maxLen + 31) / 32; u++) {
        unsigned int lMem;
        unsigned int rMem;
        if (u < MemLen) {
            lMem = pMem[u];
        }
        else
        {
            lMem = 0;
        }
        if (u < bf.MemLen) {
            rMem = bf.pMem[u];
        }
        else
        {
            rMem = 0;
        }
        res.pMem[u] = lMem | rMem;
    }
    return res;
}

TBitField TBitField::operator&(const TBitField& bf) {
    int maxLen;
    if (BitLen > bf.BitLen) {
        maxLen = BitLen;
    }
    else {
        maxLen = bf.BitLen;
    }
    TBitField res(maxLen);

    for (int u = 0; u < (maxLen + 31) / 32; u++) {
        unsigned int lMem;
        unsigned int rMem;
        if (u < MemLen) {
            lMem = pMem[u];
        }
        else
        {
            lMem = 0;
        }
        if (u < bf.MemLen) {
            rMem = bf.pMem[u];
        }
        else
        {
            rMem = 0;
        }
        res.pMem[u] = lMem & rMem;
    }
    return res;
}


TBitField TBitField::operator~() {
    TBitField tmp(BitLen);
    for (int u = 0; u < MemLen; u++) {
        tmp.pMem[u] = (unsigned int)~pMem[u];
    }
    int last = BitLen % (SIZE * 8);
    if (last > 0) {
        unsigned int mask = (1 << last) - 1; 
        tmp.pMem[MemLen - 1] &= (unsigned int)mask;
    }
    return tmp;
}


istream& operator>>(istream& istr, TBitField& bf) {
    for (int i = 0; i < bf.GetLength(); i++) {
        unsigned int bit;
        istr >> bit;
        if (bit) {
            bf.SetBit(i);
        }
        else {
            bf.ClrBit(i);
        }
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) { 
    for (int i = 0; i < bf.GetLength(); i++) {
        ostr << bf.GetBit(i);
    }
    return ostr;
}
