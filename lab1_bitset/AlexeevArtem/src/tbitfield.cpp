// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if(len < 0) throw -1;
    BitLen = len;
    if (len % (sizeof(TELEM) * 8) != 0)
        MemLen = len / (sizeof(TELEM) * 8) + 1;
    else
        MemLen = len / (sizeof(TELEM) * 8);
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}
int TBitField::GetMemIndex(const int n) const  // индекс в pМем для бита n
{
	if(n < 0) throw -1;
    if (n < BitLen) {
        int ind = n % (sizeof(TELEM) * 8);
        return ind;
    }
    else {
        throw "1";
    }
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    TELEM mask = 1 << n;
    return mask;
}

// доступ к битам битового поля
int TBitField::GetLength() const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if(n < 0) throw -1;
    pMem[n / (sizeof(TELEM) * 8)] = pMem[n / (sizeof(TELEM) * 8)] | GetMemMask(GetMemIndex(n));
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if(n < 0) throw -1;
    pMem[n / (sizeof(TELEM) * 8)] = pMem[n / (sizeof(TELEM) * 8)] & ~GetMemMask(GetMemIndex(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if(n < 0) throw -1;
    TELEM a = pMem[n / (sizeof(TELEM) * 8)];
    TELEM b = GetMemMask(GetMemIndex(n));
    if (a & b)
        return 1;
    return 0;
}

// битовые операции
TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    delete[] pMem;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen) return false;
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i]) return false;
    }
    return true;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen) return true;
    for (int i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i]) return true;
    }
    return false;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    if (BitLen < bf.BitLen) {
        TBitField a(bf);
        for (int i = 0; i < MemLen; i++) {
            a.pMem[i] = pMem[i] | bf.pMem[i];
        }
        return a;
    }
    else {
        TBitField a(*this);
        for (int i = 0; i < bf.MemLen; i++) {
            a.pMem[i] = pMem[i] | bf.pMem[i];
        }
        return a;
    }
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    if (BitLen < bf.BitLen) {
        TBitField a(bf.BitLen);
        for (int i = 0; i < MemLen; i++) {
            a.pMem[i] = pMem[i] & bf.pMem[i];
        }
        return a;
    }
    else {
        TBitField a(BitLen);
        for (int i = 0; i < bf.MemLen; i++) {
            a.pMem[i] = pMem[i] & bf.pMem[i];
        }
        return a;
    }

}

TBitField TBitField::operator~() // отрицание
{
    TBitField a(BitLen);
    for (int i = 0; i < MemLen-1; i++) {
        a.pMem[i] = ~pMem[i];
    }
    TELEM z = 0;
    for (int i = 0; i < BitLen % (sizeof(TELEM) * 8); i++) {
        z += 1 << i;
    }
    a.pMem[MemLen - 1] = pMem[MemLen - 1] ^ z;
    return a;
}

// ввод/вывод
std::istream &operator>>(std::istream &istr, TBitField &bf) // ввод
{
    char ss[255];
    istr.getline(ss, 255);
    return istr;
}

std::ostream &operator<<(std::ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = bf.BitLen - 1; i >= 0; i--) {
        if (bf.pMem[i / (sizeof(TELEM)*8)] & bf.GetMemMask(bf.GetMemIndex(i)))
            ostr << '1';
        else
            ostr << '0';
    }
    return ostr;
}